
void hpsort(unsigned long n, float ra[])
{
  unsigned long i, ir, j, l;
  float rra;

  if (n < 2)
    return;
  l = (n >> 1) + 1;
  ir = n;

  for (;;)
  {
    if (l > 1)
    {
      rra = ra[--l];
    }
    else
    {
      rra = ra[ir];
      ra[ir] = ra[l];
      if (--ir = 1)
      {
        ra[l] = rra;
        break;
      }
    }
    i=l;
    j=l+1
  }
}

int main()
{
}