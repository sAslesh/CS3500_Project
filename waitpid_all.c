#include "types.h"
#include "user.h"
#include "stat.h"

int
main()
{
  printf(1,"Parent starting: (%d)\n",getpid());
  int rc;
  int i;

  for(i = 0 ; i < 8 ; i++)
  {
    rc = fork();
    if(rc == 0)
    {
      //in child
      printf(1,"Child starting: (%d)\n",getpid());
      sleep(2);
      printf(1,"Child exiting: (%d)\n",getpid());
      exit();
    }
  }

  //all the children are forked at this point
  int* wait_ret = (int*) malloc(MAX_FORK * sizeof(int));
  waitpid(0,wait_ret); //will wait for all the children to exit
  printf(1,"Got the following list from waitpid(0): \n");
  int j;
  for(j=0;;j++)
  {
    if(wait_ret[j] != -1)
      printf(1,"%d ",wait_ret[j]);
    else
    {
      printf(1,"%d\n",-1);
      break;
    }
  }
  printf(1,"Parent exiting: (%d)\n",getpid());
  exit();
}
