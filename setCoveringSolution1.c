#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct point
{
    int var;
    struct point * next;
}points;
typedef struct sets
{
    int idx;
    int number;
    points * next;
    struct sets *next_set;
}sets;
void QuickSort(sets *Head,sets *Tail)
{
	if(Head->next_set!=Tail&&Head->next_set->next_set!=Tail)
	{
		sets *KeyP=Head->next_set;
		sets *LP=Head;
		sets *RP=KeyP;
		sets *IncP=KeyP->next_set;
		while(IncP!=Tail)
		{
			if(IncP->number>KeyP->number)
				LP=LP->next_set=IncP;
			else
				RP=RP->next_set=IncP;
			IncP=IncP->next_set;
		}
		LP->next_set=KeyP;
		RP->next_set=Tail;


		QuickSort(Head,KeyP);
		QuickSort(KeyP,Tail);
	}
}
void insert(sets *head, int idx,points *p)
{
    sets *h=head->next_set;
    for(int i=0;i<idx;i++)
        h=h->next_set;
    points *q=h->next;
    if(q->next==NULL)
    {
        p->next=q->next;
        q->next=p;
    }
    else
    {
        while(q->next!=NULL&&q->next->var<p->var)
            q=q->next;
        p->next=q->next;
        q->next=p;
    }
    h->number++;
}
points * init_points_set(int N_points)
{
    points *L=(points*)malloc(sizeof(points));
    L->next=NULL;
    L->var=-1;
    for(int i=N_points-1;i>=0;i--)
    {
        points *pl=(points*)malloc(sizeof(points));
        pl->var=i;
        pl->next = L->next;
        L->next=pl;
    }
    return L;
}
sets * init(int N_sets)
{
    sets *head=(sets*)malloc(sizeof(sets));
    head->idx=-1;
    head->next=NULL;
    head->number=-1;
    head->next_set=NULL;
    for(int i=N_sets-1;i>=0;i--)
    {
        sets *s=(sets*)malloc(sizeof(sets));
        s->idx=i;
        s->next=(points *)malloc(sizeof(points));
        s->next->next=NULL;
        sets *temp = head->next_set;
        head->next_set=s;
        s->next_set=temp;
    }
    return head;
}
int isInPoints(points *Lp, int var)
{
    if(Lp->next==NULL)
        return 0;
    else
    {
        points *p=Lp->next;
        while(p!=NULL&&p->var!=var)
            p=p->next;
        if(p==NULL)
            return 0;
        else
            return 1;
    }

}
void delete(points *Lp, int var)
{
    if(Lp->next==NULL)
        return;
    points *p=Lp;
    while(p->next->var!=var&&p->next!=NULL)
    {
        p=p->next;
    }
    if(p->next!=NULL)
    {
        points *q=p->next;
        p->next=q->next;
        free(q);
    }
}

int main()
{
    FILE *fp=fopen("SetCoveringTestData\\test04.txt","r");
    if(fp!=NULL)
    {
        int N_points, N_sets;
        fscanf(fp,"%d%d",&N_points,&N_sets);
        sets *head = init(N_sets);
        sets *st=head->next_set;
        for(int i=0;i<N_points;i++)
        {
            int idx, N_p;
            fscanf(fp,"\n%d\n%d\n",&idx, &N_p);
            for(int j=0;j<N_p;j++)
            {
                int temp;
                fscanf(fp,"%d ",&temp);
                points *p=(points *)malloc(sizeof(points));
                p->var = i;
                insert(head, temp, p);
            }

        }
        QuickSort(head, NULL);
        points *Lp= init_points_set(N_points);
        st=head->next_set;
        points *sp;
        int num=0;
        while(Lp->next!=NULL)
        {   num++;
            sp = st->next;
            while(sp->next!=NULL)
            {
                if(isInPoints(Lp, sp->next->var))
                    delete(Lp, sp->next->var);
                sp=sp->next;
            }
            st = st->next_set;

        }
        printf("¼¯ºÏÊý£º%d",num);
    }
}
