#ifndef _SCORE_H_
#define _SCORE_H_

#include "rnaz_utils.h"
#include "tree.h"
#include "treeSimulate.h"

#define UNDEF -9.0
#define MINUS_INF -99.0

#define MAX(x,y)       (((x)>(y)) ? (x) : (y))
#define MAX3(x,y,z)    (MAX(  (MAX((x),(y))) ,(z)))

typedef struct _bgModel bgModel;

struct _bgModel {

  float scores[4];
  float probs[4];
  float kappa;
  float dist;
  float freqs[4];
  int** matrix;

};

typedef struct _segmentStats segmentStats;

struct _segmentStats {

  int startSite;
  int endSite;
  int strand;
  int frame;
  int start;
  int end;
  char *name;
  float score;
  float pvalue;
  
};

/* Values set in main() */
int ntMap[256]; 

extern int transcode[4][4][4];

float probHKY(int i, int j, float d, float freqs[4], float kappa);

int** getScoringMatrix();

void freeScoringMatrix(int** matrix);

void calculateBG(bgModel* models);

int compareScores(const void * a, const void * b);

void stripGaps(struct aln* AS[]);

void countFreqsMono(const struct aln *alignment[], float freqs[]);

float* sumOfPairScore(bgModel* models, const struct aln *alignment[],int from, int to);

float* getCumSum(float* scores, int N);

bgModel* getModelMatrix(TTree* tree, struct aln *alignment[], float kappa);

void freeModelMatrix(bgModel* models, int N);

void getExtremeValuePars(TTree* tree, const struct aln *alignment[], 
                         int sampleN, float* parMu, float* parLambda);

segmentStats* getHSS(float** S, const struct aln** inputAln,  char strand, float parMu, float parLambda, float cutoff);


void getPairwiseScoreMatrix(bgModel* models, const struct aln *alignment[]);
float** getMultipleScoreMatrix(float**** Sk, bgModel* models, const struct aln *alignment[]);

float* backtrack(float**** S, int k, int from, int to, const struct aln *alignment[]);

void freeSk (float**** S, const struct aln *alignment[]);
void freeS (float** S, const struct aln *alignment[]);

segmentStats* scoreAln(const struct aln *alignment[], TTree* tree, float kappa, float parMu, float parLambda);

bgModel* getModels(TTree* tree, struct aln *alignment[], float kappa);


#endif