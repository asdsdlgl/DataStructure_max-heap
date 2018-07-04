#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define maxsize 200
typedef struct{
	int key;
}element;
element heap[maxsize];
int n = 0;
void push(element item){
	int i;
	i = ++n;
	while((i!=1)&&(item.key>heap[i/2].key)){
		heap[i]=heap[i/2];
		i/=2;
	}
	heap[i]=item;
}
void changeorder(int pos,int changenum){
	int i=pos,flag=1,flag2=1,j,temp;
	while(i!=1&&heap[i/2].key<changenum){
		heap[i] = heap[i/2];
		heap[i/2].key = changenum;
		i/=2;
		flag = 0;
	}
	while(flag&&(2*i+2)<=n&&(changenum<heap[2*i].key||changenum<heap[2*i+1].key)){
		if(heap[2*i].key>heap[2*i+1].key){
			heap[i] = heap[2*i];
			heap[2*i].key = changenum;
			i*=2;
			flag2 = 0;
		}else if(heap[2*i].key<heap[2*i+1].key){
			heap[i] = heap[2*i+1];
			heap[2*i+1].key = changenum;
			i*=2;
			i++;
			flag2 = 0;
		}
	}
	if(flag&&flag2)heap[i].key = changenum;
	
	if(n%2==0&&heap[n].key>heap[n/2].key){
		temp = heap[n/2].key;
		heap[n/2].key = heap[n].key;
		heap[n].key = temp;
	}
	if(n%2==1){ 
		if(heap[n].key>heap[n-1].key&&heap[n].key>heap[n/2].key){
			temp = heap[n/2].key;
			heap[n/2] = heap[n];
			heap[n].key = temp;
		}else if(heap[n].key<heap[n-1].key&&heap[n-1].key>heap[n/2].key){
			temp = heap[n/2].key;
			heap[n/2] = heap[n-1];
			heap[n-1].key = temp;
		}
	}
}
element pop(){
	int parent,child;
	element temp,item;
	item = heap[1];
	temp = heap[n--];
	parent = 1;
	child = 2;
	while(child<=n){
		if(child<n&&(heap[child].key<heap[child+1].key))
			child++;
			if(temp.key>=heap[child].key)break;
			heap[parent] = heap[child];
			parent = child;
			child *= 2;
	}
	heap[parent] = temp;
	return item;
}
int main(){
		FILE *fp;
		char dot,yesno;
		int num,i,j=2,count=0,choicenum,changenum,flag=0,flag2 = 0;
		double duration;
		clock_t start,end;
		element temp;
		fp = fopen("in.txt","r");
		printf("Create Max Heap :\n");
		while(fscanf(fp,"%d%c",&num,&dot)!=EOF){
			temp.key = num;
			push(temp);
		}
		while(1){
			count = 0;
			j = 2;
			printf("Max Heap :\n");
			for(i=1;i<=n;i++){
				printf("%d ",heap[i].key);
				if(i==1)printf("\n");
				else if(count%j==0){
					printf("\n");
					j = j*2;
					count = 0;
				}
				count++;
			}
			if(flag){
				duration = ((clock()-start))/(double)(CLOCKS_PER_SEC);
				printf("\nSpend time : %f sec\n",duration);
			}
			flag = 0;
			printf("\n");
			
			while(!flag2){
				printf("Delete element ? (Y/N) :\n");
				scanf(" %c",&yesno);
				if(yesno=='n'||yesno=='N')flag2 = 1;
				else if(yesno=='y'||yesno=='Y')break;
				else{
					printf("your input should be (Y/N)\nTRY AGAIN!!\n");
				}
			}
			if(flag2)break;
			
			printf("Choice element : \n");
			scanf("%d",&choicenum);
			start = clock();
			for(i=1;i<=n;i++)
				if(heap[i].key==choicenum){
					changeorder(i,heap[1].key+1);
					pop();
					flag = 1;
					break;
				}
			if(!flag)printf("your input didn't define in heap!!\nTRY AGAIN!!\n");
		}
		fclose(fp);
}
