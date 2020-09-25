int dbl_compare(const void *a, const void *b)
{
  return ( (*(double *) a - *(double *) b) ? -1 : 1 );
}