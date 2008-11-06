#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include "rnaz_utils.h"

#include "treeSimulate.h"

#include "global.h"
#include "treefile.h"
#include "evolve.h"
#include "model.h"
#include "nucmodels.h"
#include "aamodels.h"
#include "progress.h"
#include "twister.h"

extern int model;
extern int numStates;
extern int isNucModel;
extern int userFreqs;
extern int equalFreqs;
extern int numSites;
extern double tstv;
extern double nucFreq[NUM_NUC];
extern int numTaxa;
char* P;


void simulateTree(TTree* tree, double freqs[], double kap, int L){
  
  int i,j,k;
  int* tmp;
  double** matrix;
  double freqR,freqY,freqAG,freqCT;
  double freqA, freqC, freqG, freqT;

  isNucModel = 1;
	numStates = 4;
  model=0; /*0 means HKY, take care model constants are a tricky in
             seqgen and if set to defined constant HKY this does not
             work*/

  equalFreqs = 0;
	equalTstv = 0;

  freqA=nucFreq[0]=freqs[0];
  freqC=nucFreq[1]=freqs[1];
  freqG=nucFreq[2]=freqs[2];
  freqT=nucFreq[3]=freqs[3];
  
  freqR=freqA+freqG;
  freqY=freqC+freqT;
  freqAG=freqA*freqG;
  freqCT=freqC*freqT;

  tstv=kap*(freqAG+freqCT)/(freqR*freqY);
  
  numSites=L;

  randomSeed = CreateSeed();
	SetSeed(randomSeed);
	CreateRates();
  
  numTaxa=tree->numTips;

  CreateSequences(tree, numSites);
  SetModel(model);
  
  EvolveSequences(tree, 0, numSites, 1.0, NULL);
  
  FreeRates();

} 


TTree* string2tree(char* treeString){
  
  FILE * tmpfh;
  TTree* tree;
  int dummy1;
  double dummy2;
  
  tmpfh = tmpfile();
  fprintf(tmpfh,"%s",treeString);
  rewind(tmpfh); 
  tree=NewTree();
  ReadTree(tmpfh, tree, 0, 0, NULL, &dummy1, &dummy2);
  fclose(tmpfh);
  return tree;

}


double** getDistanceMatrix(TTree* tree, struct aln *alignment[]){

  TNode* LCA;
  TNode* nodeA=NULL;
  TNode* nodeB=NULL;
  double sum=0.0;
  double** matrix;
  int N,i,j,k;

  for (N=0; alignment[N]!=NULL; N++);

  matrix=(double**)space(sizeof(double*)*N);

  for (i=0;i<N;i++){
    matrix[i]=(double*)space(sizeof(double)*N);
  }

       
  for (i=0;alignment[i] != NULL; i++){
      
    for (j=0;alignment[j] != NULL; j++){

      if (i==j){
        matrix[i][j]=0.0;
        continue;
      }

      if (i>j) continue;

      for (k=0;k<tree->numTips;k++){
        if (strcmp(tree->names[k],alignment[i]->name)==0){
          nodeA=tree->tips[k];
          break;
        }
      }

      for (k=0;k<tree->numTips;k++){
        if (strcmp(tree->names[k],alignment[j]->name)==0){
          nodeB=tree->tips[k];
          break;
        }
      }
        
      LCA=NULL;
      
      LCA=getLCA(tree,nodeA, nodeB);
      sum=0.0;

      while (1){
        if (nodeA != LCA){
          sum+=nodeA->length0;
          nodeA=nodeA->branch0;
        } else {
          break;
        }
      }
        
      while (1){
        if (nodeB != LCA){
          sum+=nodeB->length0;
          nodeB=nodeB->branch0;
        } else {
          break;
        }
      }
      
      matrix[i][j]=sum;
      matrix[j][i]=sum;

    }
  }
  return matrix;
}





TNode* getLCA(TTree* tree, TNode* nodeA, TNode* nodeB){

  TNode** listA;
  TNode** listB;
  TNode** tmp;
  TNode* lca;
  int i,j;
  int numAncestorsA,numAncestorsB;
  int minNumAncestors,maxNumAncestors;

  listA=(TNode**)space(sizeof(TNode*)*tree->numNodes);
  listB=(TNode**)space(sizeof(TNode*)*tree->numNodes);

  numAncestorsA=0;

  do {
    listA[numAncestorsA++]=nodeA;
    nodeA=nodeA->branch0;
  } while (nodeA != tree->root);
  listA[numAncestorsA++]=tree->root;
    
  
  numAncestorsB=0;

  do {
    listB[numAncestorsB++]=nodeB;
    nodeB=nodeB->branch0;
  } while (nodeB != tree->root);
  listB[numAncestorsB++]=tree->root;

  if (numAncestorsA < numAncestorsB){
    minNumAncestors=numAncestorsA;
    maxNumAncestors=numAncestorsB;
   
  } else {
    minNumAncestors=numAncestorsB;
    maxNumAncestors=numAncestorsA;

    tmp=listA;
    listA=listB;
    listB=tmp;
  }

  for (i=0;i<minNumAncestors;i++){
    for (j=0;j<maxNumAncestors;j++){
      if (listA[i]==listB[j]){
        lca=listA[i];

        free(listA);
        free(listB);

        return lca;
      }
    }
  }
}


void tree2aln(TTree* tree, struct aln *alignment[]){

  int i,j;
  char* seq;
  char* encodedSeq;
  FILE* tmpfh;
  
  for (i=0; i<tree->numTips; i++) {
    
    seq=(char*)space((sizeof(char))*(numSites+1));
     
    encodedSeq=tree->tips[i]->sequence;

    for (j=0; j<numSites; j++) {
      seq[j]=stateCharacters[(int)*encodedSeq];
      encodedSeq++;
    }


    alignment[i]=createAlnEntry(strdup(tree->names[i]), 
                                seq,0,0,0,'?');
  
  }

  alignment[i]=NULL;
}

 /* tree is free'd manually since the function "FreeTree" in seq-gen
     do not seem to free everything */
  
void freeSeqgenTree(TTree* tree){

  int i;
  TNode *node, *nextNode;

  for (i=0;i<tree->capacity;i++){
    free(tree->names[i]);
  }

  node=tree->nodeList;
  while (node != NULL){
    nextNode=node->next;
    free(node->sequence);
    free(node);
    node=nextNode;
  }

  free(tree->names);
  free(tree->tips);
  free(tree);

}
