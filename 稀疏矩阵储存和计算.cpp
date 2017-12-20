#include <stdio.h>
using namespace std;


typedef struct Node
{int Row, Col;
 int Elem;
 struct Node *Right, *Down;
}Node, *Link;


typedef struct 
{Link *RowHead, *ColHead;
 int RowNumber,ColNumber,ElemNumber;
}CrossList;


int Reset(CrossList *M)
{(*M).RowHead=NULL;
 (*M).ColHead=NULL;
 (*M).RowNumber=0;
 (*M).ColHead=0;
 (*M).ElemNumber=0;
 return 1;
}


int Create(CrossList *M)
{int i,j,k,m,t;
 int e;
 Node *p, *q;

 scanf("%d %d %d",&m,&m,&t);
 (*M).RowNumber=m;
 (*M).ColNumber=m;
 (*M).ElemNumber=t;
 (*M).RowHead = new Link[m];
 (*M).ColHead = new Link[m];
 for (i=0;i<m;i++) (*M).RowHead[i]=NULL;
 for (i=0;i<m;i++) (*M).ColHead[i]=NULL;

 for (k=0;k<t;k++)
 {scanf("%d %d %d",&i,&j,&e);
  p= new Node;
  p->Row=i;p->Col=j;p->Elem=e;

  if ((*M).RowHead[i]==NULL||(*M).RowHead[i]->Col>j)
  {p->Right=(*M).RowHead[i];
   (*M).RowHead[i]=p;}
  else 
  {for (q=(*M).RowHead[i];q->Right!=NULL&&q->Right->Col<j;q=q->Right);
   p->Right=q->Right;
   q->Right=p;}

  if ((*M).ColHead[j]==NULL||(*M).ColHead[j]->Row>i)
  {p->Down=(*M).ColHead[j];
  (*M).ColHead[j]=p;}
  else
  {for (q=(*M).ColHead[j];q->Down!=NULL&&q->Down->Row<i;q=q->Down);
   p->Down=q->Down;
   q->Down=p;}
 }

  return 0;
}


 int Display(CrossList M)
 {int i;
  Link p;

  for (i=0;i<M.RowNumber;i++)
  {p=M.RowHead[i];
   while (p!=NULL) 
		{if (p->Elem==0) p=p->Right;
		 else {printf("%d %d %d\n",p->Row,p->Col,p->Elem);
                 p=p->Right;
		         }
		}
  }
  return 0;
}


int Copy(CrossList M, CrossList *C)
{int i;
 Link p,q,pointer;

 (*C).RowNumber=M.RowNumber;
 (*C).ColNumber=M.ColNumber;
 (*C).ElemNumber=M.ElemNumber;

 (*C).RowHead = new Link[(*C).RowNumber];
 (*C).ColHead = new Link[(*C).ColNumber];
 for (i=0;i<(*C).RowNumber;i++) (*C).RowHead[i]=NULL;
 for (i=0;i<(*C).ColNumber;i++) (*C).ColHead[i]=NULL;

 for (i=0;i<M.RowNumber;i++)
 {p=M.RowHead[i];
  while (p!=NULL)
		{q=new Node;
         q->Row=p->Row;
         q->Col=p->Col;
		 q->Elem=p->Elem;

		 if ((*C).RowHead[i]==NULL) 
		 {(*C).RowHead[i]=q;
		  (*C).RowHead[i]->Right=NULL;
		 }
		 else 
		 {pointer=(*C).RowHead[i];
		  while (pointer->Right!=NULL) pointer=pointer->Right;
		  pointer->Right=q;
		  q->Right=NULL;
		 }
		 
		 if ((*C).ColHead[q->Col]==NULL) 
		 {(*C).ColHead[q->Col]=q;
		  q->Down=NULL;
		 }
		 else 
		 {pointer=(*C).ColHead[q->Col];
		  while (pointer->Down!=NULL) pointer=pointer->Down;
		  pointer->Down=q;
		  q->Down=NULL;
		 }

		 p=p->Right;
        }
  q->Right=NULL;
 }
 return 0;
}


int Transpose(CrossList M, CrossList *T)
{int temp,i;
 Link *Head,p,q,r;

 Copy(M,T);

 temp=(*T).ColNumber;
 (*T).ColNumber=(*T).RowNumber;
 (*T).RowNumber=temp;

 Head=(*T).ColHead;
 (*T).ColHead=(*T).RowHead;
 (*T).RowHead=Head;

 for (i=0;i<(*T).RowNumber;i++)
 {p=(*T).RowHead[i];
  while (p!=NULL)
		{q=p->Down;

         temp=p->Row;
		 p->Row=p->Col;
		 p->Col=temp;

		 r=p->Down;
		 p->Down=p->Right;
		 p->Right=r;
             
		 p=q;
         }
 }
 return 0;
}


int Add(CrossList M, CrossList N, CrossList *S)
{int i;
 Link p,ps,pr,pc;
 Link *Column;

 (*S).RowNumber=M.RowNumber;
 (*S).ColNumber=M.ColNumber;
 (*S).ElemNumber=0;

 (*S).RowHead=new Link[(*S).RowNumber];
 (*S).ColHead=new Link[(*S).ColNumber];
 for (i=0;i<(*S).RowNumber;i++) (*S).RowHead[i]=NULL;
 for (i=0;i<(*S).ColNumber;i++) (*S).ColHead[i]=NULL;

 Column=new Link[(*S).ColNumber];
 for (i=0;i<(*S).ColNumber;i++) Column[i]=NULL;

 for (i=0;i<(*S).RowNumber;i++)
 {pr=M.RowHead[i];
  pc=N.RowHead[i];
  while (pr!=NULL&&pc!=NULL)
		{if (pr->Col<pc->Col) 
		 {p=new Node;
		  (*S).ElemNumber++;

		  p->Row=i;
		  p->Col=pr->Col;
		  p->Elem=pr->Elem;

		  p->Right=NULL;
		  pr=pr->Right;}
		 else if (pr->Col>pc->Col)
          {p=new Node;
           (*S).ElemNumber++;

		   p->Row=i;
		   p->Col=pc->Col;
		   p->Elem=pc->Elem;

		   p->Right=NULL;
		   pc=pc->Right;
		  }
		 else 
		 {p=new Node;
		  (*S).ElemNumber++;
		  
		  p->Row=i;
		  p->Col=pr->Col;
		  p->Elem=pr->Elem+pc->Elem;

		  p->Right=NULL;
		  pr=pr->Right;
		  pc=pc->Right;
		 }

		 if ((*S).RowHead[i]==NULL) (*S).RowHead[i]=ps=p;
		 else 
		 {ps->Right=p;
		  ps=ps->Right;
		 }

		 if ((*S).ColHead[p->Col]==NULL) (*S).ColHead[p->Col]=Column[p->Col]=p;
		 else 
		 {Column[p->Col]->Down=p;
		  Column[p->Col]=Column[p->Col]->Down;
		 }
        }   

  while (pr!=NULL) 
		{p=new Node;
		 (*S).ElemNumber++;

		 p->Row=i;
		 p->Col=pr->Col;
		 p->Elem=pr->Elem;

		 p->Right=NULL;
		 pr=pr->Right;

		 if ((*S).RowHead[i]==NULL) (*S).RowHead[i]=ps=p;
		 else 
		 {ps->Right=p;
		  ps=ps->Right;
		 }

		 if ((*S).ColHead[p->Col]==NULL) (*S).ColHead[p->Col]=Column[p->Col]=p;
		 else
		 {Column[p->Col]->Down=p;
		  Column[p->Col]=Column[p->Col]->Down;
		 }
        }

  while (pc!=NULL)
		{p=new Node;
         (*S).ElemNumber++;

		 p->Row=i;
		 p->Col=pc->Col;
		 p->Elem=pc->Elem;

		 p->Right=NULL;
		 pc=pc->Right;

		 if ((*S).RowHead[i]==NULL) (*S).RowHead[i]=ps=p;
		 else
		 {ps->Right=p;
		  ps=ps->Right;
		 }

		 if ((*S).ColHead[p->Col]==NULL) (*S).ColHead[p->Col]=Column[p->Col]=p;
		 else 
		 {Column[p->Col]->Down=p;
		  Column[p->Col]=Column[p->Col]->Down;
		 }
        }
 }

 for (i=0;i<(*S).ColNumber;i++) 
 if (Column[i]!=NULL) Column[i]->Down=NULL;
 delete(Column);

 return 0;
}


int Multiply(CrossList M, CrossList N, CrossList *S)
{int i,j;
 int Element;
 Link p,pr,pc,pointer;

 Reset(S);
 (*S).RowNumber=M.RowNumber;
 (*S).ColNumber=M.ColNumber;
 (*S).ElemNumber=0;

 (*S).RowHead=new Link[(*S).RowNumber];
 (*S).ColHead=new Link[(*S).ColNumber];
 for (i=0;i<(*S).RowNumber;i++) (*S).RowHead[i]=NULL;
 for (i=0;i<(*S).ColNumber;i++) (*S).ColHead[i]=NULL;

 for (i=0;i<(*S).RowNumber;i++)
	 for (j=0;j<(*S).ColNumber;j++)
	 {pr=M.RowHead[i];
      pc=N.ColHead[j];
	  Element=0;
	  while (pr!=NULL&&pc!=NULL)
			{if (pc->Row<pr->Col) pc=pc->Down;
			 else if(pc->Row>pr->Col) pr=pr->Right;
			        else
					{Element=Element+pr->Elem*pc->Elem;
			         pr=pr->Right;
					 pc=pc->Down;
			        }
			}
	  
	  if (Element!=0) 
	  {(*S).ElemNumber++;
	   p=new Node;
	   
	   p->Row=i;
	   p->Col=j;
	   p->Elem=Element;
	   p->Right=NULL;
	   p->Down=NULL;

	   if ((*S).RowHead[i]==NULL) (*S).RowHead[i]=p;
	   else 
	   {pointer=(*S).RowHead[i];
	    while (pointer->Right!=NULL) pointer=pointer->Right;
		pointer->Right=p;
	   }

	   if ((*S).ColHead[j]==NULL) (*S).ColHead[j]=p;
	   else 
	   {pointer=(*S).ColHead[j];
	    while (pointer->Down!=NULL) pointer=pointer->Down;
		pointer->Down=p;
	   }
	  }
     } 
      
return 0;
}


int main()
{CrossList A,B,C,D;

 Reset(&A);
 Reset(&B);
 Create(&A);
 Transpose(A,&B);
 Add(A,B,&C);
 Multiply(A,B,&D);
 Display(B);
 Display(C);
 Display(D);

 return 0;
}