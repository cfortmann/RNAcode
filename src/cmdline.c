/*
  File autogenerated by gengetopt version 2.19.1
  generated with the following command:
  gengetopt -F cmdline --unamed-opts --no-handle-version --no-handle-help --no-handle-error 

  The developers of gengetopt consider the fixed text that goes in all
  gengetopt output files to be in the public domain:
  we make no copyright claims on it.
*/

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getopt.h"

#include "cmdline.h"

const char *gengetopt_args_info_purpose = "";

const char *gengetopt_args_info_usage = "Usage: " CMDLINE_PARSER_PACKAGE " [OPTIONS]... [FILES]...";

const char *gengetopt_args_info_description = "";

const char *gengetopt_args_info_help[] = {
  "  -h, --help             Print help and exit",
  "  -V, --version          Print version and exit",
  "  -o, --outfile=STRING   Output filename",
  "  -n, --num-samples=INT  Number of samples",
  "  -v, --verbose          verbose  (default=off)",
  "  -e, --cutoff=FLOAT     e-value cutoff",
  "  -g, --gtf              GTF output  (default=off)",
  "  -f, --fast-sampling    Fast sampling  (default=off)",
    0
};

static
void clear_given (struct gengetopt_args_info *args_info);
static
void clear_args (struct gengetopt_args_info *args_info);

static int
cmdline_parser_internal (int argc, char * const *argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required, const char *additional_error);


static char *
gengetopt_strdup (const char *s);

static
void clear_given (struct gengetopt_args_info *args_info)
{
  args_info->help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->outfile_given = 0 ;
  args_info->num_samples_given = 0 ;
  args_info->verbose_given = 0 ;
  args_info->cutoff_given = 0 ;
  args_info->gtf_given = 0 ;
  args_info->fast_sampling_given = 0 ;
}

static
void clear_args (struct gengetopt_args_info *args_info)
{
  args_info->outfile_arg = NULL;
  args_info->outfile_orig = NULL;
  args_info->num_samples_orig = NULL;
  args_info->verbose_flag = 0;
  args_info->cutoff_orig = NULL;
  args_info->gtf_flag = 0;
  args_info->fast_sampling_flag = 0;
  
}

static
void init_args_info(struct gengetopt_args_info *args_info)
{
  args_info->help_help = gengetopt_args_info_help[0] ;
  args_info->version_help = gengetopt_args_info_help[1] ;
  args_info->outfile_help = gengetopt_args_info_help[2] ;
  args_info->num_samples_help = gengetopt_args_info_help[3] ;
  args_info->verbose_help = gengetopt_args_info_help[4] ;
  args_info->cutoff_help = gengetopt_args_info_help[5] ;
  args_info->gtf_help = gengetopt_args_info_help[6] ;
  args_info->fast_sampling_help = gengetopt_args_info_help[7] ;
  
}

void
cmdline_parser_print_version (void)
{
  printf ("%s %s\n", CMDLINE_PARSER_PACKAGE, CMDLINE_PARSER_VERSION);
}

void
cmdline_parser_print_help (void)
{
  int i = 0;
  cmdline_parser_print_version ();

  if (strlen(gengetopt_args_info_purpose) > 0)
    printf("\n%s\n", gengetopt_args_info_purpose);

  printf("\n%s\n\n", gengetopt_args_info_usage);

  if (strlen(gengetopt_args_info_description) > 0)
    printf("%s\n", gengetopt_args_info_description);

  while (gengetopt_args_info_help[i])
    printf("%s\n", gengetopt_args_info_help[i++]);
}

void
cmdline_parser_init (struct gengetopt_args_info *args_info)
{
  clear_given (args_info);
  clear_args (args_info);
  init_args_info (args_info);

  args_info->inputs = NULL;
  args_info->inputs_num = 0;
}

static void
cmdline_parser_release (struct gengetopt_args_info *args_info)
{
  
  unsigned int i;
  if (args_info->outfile_arg)
    {
      free (args_info->outfile_arg); /* free previous argument */
      args_info->outfile_arg = 0;
    }
  if (args_info->outfile_orig)
    {
      free (args_info->outfile_orig); /* free previous argument */
      args_info->outfile_orig = 0;
    }
  if (args_info->num_samples_orig)
    {
      free (args_info->num_samples_orig); /* free previous argument */
      args_info->num_samples_orig = 0;
    }
  if (args_info->cutoff_orig)
    {
      free (args_info->cutoff_orig); /* free previous argument */
      args_info->cutoff_orig = 0;
    }
  
  for (i = 0; i < args_info->inputs_num; ++i)
    free (args_info->inputs [i]);
  
  if (args_info->inputs_num)
    free (args_info->inputs);
  
  clear_given (args_info);
}

int
cmdline_parser_file_save(const char *filename, struct gengetopt_args_info *args_info)
{
  FILE *outfile;
  int i = 0;

  outfile = fopen(filename, "w");

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot open file for writing: %s\n", CMDLINE_PARSER_PACKAGE, filename);
      return EXIT_FAILURE;
    }

  if (args_info->help_given) {
    fprintf(outfile, "%s\n", "help");
  }
  if (args_info->version_given) {
    fprintf(outfile, "%s\n", "version");
  }
  if (args_info->outfile_given) {
    if (args_info->outfile_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "outfile", args_info->outfile_orig);
    } else {
      fprintf(outfile, "%s\n", "outfile");
    }
  }
  if (args_info->num_samples_given) {
    if (args_info->num_samples_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "num-samples", args_info->num_samples_orig);
    } else {
      fprintf(outfile, "%s\n", "num-samples");
    }
  }
  if (args_info->verbose_given) {
    fprintf(outfile, "%s\n", "verbose");
  }
  if (args_info->cutoff_given) {
    if (args_info->cutoff_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "cutoff", args_info->cutoff_orig);
    } else {
      fprintf(outfile, "%s\n", "cutoff");
    }
  }
  if (args_info->gtf_given) {
    fprintf(outfile, "%s\n", "gtf");
  }
  if (args_info->fast_sampling_given) {
    fprintf(outfile, "%s\n", "fast-sampling");
  }
  
  fclose (outfile);

  i = EXIT_SUCCESS;
  return i;
}

void
cmdline_parser_free (struct gengetopt_args_info *args_info)
{
  cmdline_parser_release (args_info);
}


/* gengetopt_strdup() */
/* strdup.c replacement of strdup, which is not standard */
char *
gengetopt_strdup (const char *s)
{
  char *result = NULL;
  if (!s)
    return result;

  result = (char*)malloc(strlen(s) + 1);
  if (result == (char*)0)
    return (char*)0;
  strcpy(result, s);
  return result;
}

int
cmdline_parser (int argc, char * const *argv, struct gengetopt_args_info *args_info)
{
  return cmdline_parser2 (argc, argv, args_info, 0, 1, 1);
}

int
cmdline_parser2 (int argc, char * const *argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required)
{
  int result;

  result = cmdline_parser_internal (argc, argv, args_info, override, initialize, check_required, NULL);

  return result;
}

int
cmdline_parser_required (struct gengetopt_args_info *args_info, const char *prog_name)
{
  return EXIT_SUCCESS;
}

int
cmdline_parser_internal (int argc, char * const *argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required, const char *additional_error)
{
  int c;	/* Character of the parsed option.  */

  int error = 0;
  struct gengetopt_args_info local_args_info;

  if (initialize)
    cmdline_parser_init (args_info);

  cmdline_parser_init (&local_args_info);

  optarg = 0;
  optind = 0;
  opterr = 1;
  optopt = '?';

  while (1)
    {
      int option_index = 0;
      char *stop_char;

      static struct option long_options[] = {
        { "help",	0, NULL, 'h' },
        { "version",	0, NULL, 'V' },
        { "outfile",	1, NULL, 'o' },
        { "num-samples",	1, NULL, 'n' },
        { "verbose",	0, NULL, 'v' },
        { "cutoff",	1, NULL, 'e' },
        { "gtf",	0, NULL, 'g' },
        { "fast-sampling",	0, NULL, 'f' },
        { NULL,	0, NULL, 0 }
      };

      stop_char = 0;
      c = getopt_long (argc, argv, "hVo:n:ve:gf", long_options, &option_index);

      if (c == -1) break;	/* Exit from `while (1)' loop.  */

      switch (c)
        {
        case 'h':	/* Print help and exit.  */
          if (local_args_info.help_given)
            {
              fprintf (stderr, "%s: `--help' (`-h') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->help_given && ! override)
            continue;
          local_args_info.help_given = 1;
          args_info->help_given = 1;
          cmdline_parser_free (&local_args_info);
          return 0;

        case 'V':	/* Print version and exit.  */
          if (local_args_info.version_given)
            {
              fprintf (stderr, "%s: `--version' (`-V') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->version_given && ! override)
            continue;
          local_args_info.version_given = 1;
          args_info->version_given = 1;
          cmdline_parser_free (&local_args_info);
          return 0;

        case 'o':	/* Output filename.  */
          if (local_args_info.outfile_given)
            {
              fprintf (stderr, "%s: `--outfile' (`-o') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->outfile_given && ! override)
            continue;
          local_args_info.outfile_given = 1;
          args_info->outfile_given = 1;
          if (args_info->outfile_arg)
            free (args_info->outfile_arg); /* free previous string */
          args_info->outfile_arg = gengetopt_strdup (optarg);
          if (args_info->outfile_orig)
            free (args_info->outfile_orig); /* free previous string */
          args_info->outfile_orig = gengetopt_strdup (optarg);
          break;

        case 'n':	/* Number of samples.  */
          if (local_args_info.num_samples_given)
            {
              fprintf (stderr, "%s: `--num-samples' (`-n') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->num_samples_given && ! override)
            continue;
          local_args_info.num_samples_given = 1;
          args_info->num_samples_given = 1;
          args_info->num_samples_arg = strtol (optarg, &stop_char, 0);
          if (!(stop_char && *stop_char == '\0')) {
            fprintf(stderr, "%s: invalid numeric value: %s\n", argv[0], optarg);
            goto failure;
          }
          if (args_info->num_samples_orig)
            free (args_info->num_samples_orig); /* free previous string */
          args_info->num_samples_orig = gengetopt_strdup (optarg);
          break;

        case 'v':	/* verbose.  */
          if (local_args_info.verbose_given)
            {
              fprintf (stderr, "%s: `--verbose' (`-v') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->verbose_given && ! override)
            continue;
          local_args_info.verbose_given = 1;
          args_info->verbose_given = 1;
          args_info->verbose_flag = !(args_info->verbose_flag);
          break;

        case 'e':	/* e-value cutoff.  */
          if (local_args_info.cutoff_given)
            {
              fprintf (stderr, "%s: `--cutoff' (`-e') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->cutoff_given && ! override)
            continue;
          local_args_info.cutoff_given = 1;
          args_info->cutoff_given = 1;
          args_info->cutoff_arg = (float)strtod (optarg, &stop_char);
          if (!(stop_char && *stop_char == '\0')) {
            fprintf(stderr, "%s: invalid numeric value: %s\n", argv[0], optarg);
            goto failure;
          }
          if (args_info->cutoff_orig)
            free (args_info->cutoff_orig); /* free previous string */
          args_info->cutoff_orig = gengetopt_strdup (optarg);
          break;

        case 'g':	/* GTF output.  */
          if (local_args_info.gtf_given)
            {
              fprintf (stderr, "%s: `--gtf' (`-g') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->gtf_given && ! override)
            continue;
          local_args_info.gtf_given = 1;
          args_info->gtf_given = 1;
          args_info->gtf_flag = !(args_info->gtf_flag);
          break;

        case 'f':	/* Fast sampling.  */
          if (local_args_info.fast_sampling_given)
            {
              fprintf (stderr, "%s: `--fast-sampling' (`-f') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->fast_sampling_given && ! override)
            continue;
          local_args_info.fast_sampling_given = 1;
          args_info->fast_sampling_given = 1;
          args_info->fast_sampling_flag = !(args_info->fast_sampling_flag);
          break;


        case 0:	/* Long option with no short option */
        case '?':	/* Invalid option.  */
          /* `getopt_long' already printed an error message.  */
          goto failure;

        default:	/* bug: option not considered.  */
          fprintf (stderr, "%s: option unknown: %c%s\n", CMDLINE_PARSER_PACKAGE, c, (additional_error ? additional_error : ""));
          abort ();
        } /* switch */
    } /* while */




  cmdline_parser_release (&local_args_info);

  if ( error )
    return (EXIT_FAILURE);

  if (optind < argc)
    {
      int i = 0 ;
      int found_prog_name = 0;
      /* whether program name, i.e., argv[0], is in the remaining args
         (this may happen with some implementations of getopt,
          but surely not with the one included by gengetopt) */

      i = optind;
      while (i < argc)
        if (argv[i++] == argv[0]) {
          found_prog_name = 1;
          break;
        }
      i = 0;

      args_info->inputs_num = argc - optind - found_prog_name;
      args_info->inputs =
        (char **)(malloc ((args_info->inputs_num)*sizeof(char *))) ;
      while (optind < argc)
        if (argv[optind++] != argv[0])
          args_info->inputs[ i++ ] = gengetopt_strdup (argv[optind-1]) ;
    }

  return 0;

failure:
  
  cmdline_parser_release (&local_args_info);
  return (EXIT_FAILURE);
}
