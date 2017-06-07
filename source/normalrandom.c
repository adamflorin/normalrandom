/**
* normalrandom.c: Max external to generates normally-distributed
* random numbers using the Box-Muller transform.
*
* Copyright 2014–2017 Adam Florin
*/

#include "ext.h"
#include "ext_common.h"
#include "ext_obex.h"
#include "ext_strings.h"

// External struct
typedef struct _normalrandom {
  t_object object;
  void *outlet;
} t_normalrandom;

// Method headers
t_normalrandom *normalrandom_new(
  t_symbol *s,
  long argc,
  t_atom *argv
);
void normalrandom_free(t_normalrandom *x);
void normalrandom_assist(
  t_normalrandom *x,
  void *b,
  long m,
  long a,
  char *s
);
void normalrandom_bang(t_normalrandom *x);

// External class
static t_class *s_normalrandom_class = NULL;

/** Initialize external class */
int C74_EXPORT main(void) {
  t_class *c = class_new(
    "normalrandom",
    (method)normalrandom_new,
    (method)normalrandom_free,
    sizeof(t_normalrandom),
    (method)0L,
    A_GIMME,
    0);

  class_addmethod(
    c,
    (method)normalrandom_assist,
    "assist",
    A_CANT,
    0
  );
  class_addmethod(c, (method)normalrandom_bang, "bang", 0);

  class_register(CLASS_BOX, c);
  s_normalrandom_class = c;
  return 0;
}

/** Initialize external instance */
t_normalrandom *normalrandom_new(
  t_symbol *s,
  long argc,
  t_atom *argv
) {
  t_normalrandom *x =
    (t_normalrandom *)object_alloc(s_normalrandom_class);

  x->outlet = floatout(x);

  return x;
}

/** Destroy external instance */
void normalrandom_free(t_normalrandom *x) {
}

/** Configure user tooltip prompts */
void normalrandom_assist(
  t_normalrandom *x,
  void *b,
  long m,
  long a,
  char *s
) {
  if (m == ASSIST_INLET) {
    switch (a) {
      case 0: sprintf(s, "Bang to generate random number"); break;
    }
  } else {
    switch (a) {
      case 0: sprintf(s, "Random number"); break;
    }
  }
}

/** Generate the normally distributed random number on bang */
void normalrandom_bang(t_normalrandom *x) {
  double x1 = 0.0;
  double x2 = 0.0;
  double w = 0.0;

  while ((w >= 1.0) || (w <= 0.0)) {
    x1 = 2.0 * (double)rand() / RAND_MAX - 1.0;
    x2 = 2.0 * (double)rand() / RAND_MAX - 1.0;
    w = (x1 * x2) + (x2 * x2);
  }

  w = sqrt(-2.0 * log( w ) / w);
  outlet_float(x->outlet, x1 * w);
}
