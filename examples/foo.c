int a[10];
int main (int argc, char **argv){
   int i;
   for (i=0;i<10;i++) {
	 if (i < 5)
		a[i]=0;
	 else
		a[i]=5;
   }
   int res = a[i-1];
   return res;
}

