#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

int count = 5;

char *sastojci[] = {"duvan", "rizle", "sibice"};

pthread_t agent;
pthread_t pusacDuvan;
pthread_t pusacRizle;
pthread_t pusacSibice;

sem_t agentSemafor;
sem_t pusacDuvanSemafor;
sem_t pusacRizleSemafor;
sem_t pusacSibiceSemafor;

pthread_mutex_t lock;

void *agent_f()
{
    while(1)
    {
        sem_wait(&agentSemafor);
        
        pthread_mutex_lock(&lock);
        if(count == 0) 
        {
            pthread_cancel(pusacDuvan);
            pthread_cancel(pusacRizle);
            pthread_cancel(pusacSibice);
            break;
        }
        pthread_mutex_unlock(&lock);
               
        int first = rand() % 3;
        int second = first;
        
        while(first == second)
        {
            second = rand() % 3;   
        }
        
        printf("Agent je kreirao: %s i %s\n", sastojci[first], sastojci[second]);
        
        sleep(1);
        
        switch(first + second)
        {
            case 1:
            sem_post(&pusacSibiceSemafor);
            break;
            case 2:
            sem_post(&pusacRizleSemafor);
            break;
            case 3:
            sem_post(&pusacDuvanSemafor);
            break;
            default:
            break;
        }
    }
}

void *pusac_duvan_f()
{
    while(1)
    {
        sem_wait(&pusacDuvanSemafor);
    
        pthread_mutex_lock(&lock);
        if(count == 0) 
        {
            break;
        }
        pthread_mutex_unlock(&lock);
    
        printf("\tPusac sa duvanom pravi cigaru...\n");
        sleep(1);
        printf("\tPusac sa duvanom je zapalio cigaru...\n");
        pthread_mutex_lock(&lock);
        count--;
        if(count == 0)
        {
            printf("\tAgent je zavrsio sa kreiranjem sastojaka\n");
        }
        else
        {
            printf("\tAgent kreira nove sastojke jos %d put(a)\n", count);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
        
        sem_post(&agentSemafor); 
    }
}

void *pusac_rizle_f()
{
    while(1)
    {
        sem_wait(&pusacRizleSemafor);
     
        pthread_mutex_lock(&lock);
        if(count == 0) 
        {
            break;
        }
        pthread_mutex_unlock(&lock);
        
        printf("\tPusac sa rizlama pravi cigaru...\n");
        sleep(1);
        printf("\tPusac sa rizlama je zapalio cigaru...\n");
        pthread_mutex_lock(&lock);
        count--;
        if(count == 0)
        {
            printf("\tAgent je zavrsio sa kreiranjem sastojaka\n");
        }
        else
        {
            printf("\tAgent kreira nove sastojke jos %d put(a)\n", count);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
        
        sem_post(&agentSemafor); 
    }
}

void *pusac_sibice_f()
{
    while(1)
    {
        sem_wait(&pusacSibiceSemafor);
        
        pthread_mutex_lock(&lock);
        if(count == 0) 
        {
            break;
        }
        pthread_mutex_unlock(&lock);
           
        printf("\tPusac sa sibicama pravi cigaru...\n");
        sleep(1);
        printf("\tPusac sa sibicama je zapalio cigaru...\n");
        pthread_mutex_lock(&lock);
        count--;
        if(count == 0)
        {
            printf("\tAgent je zavrsio sa kreiranjem sastojaka\n");
        }
        else
        {
            printf("\tAgent kreira nove sastojke jos %d put(a)\n", count);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
        
        sem_post(&agentSemafor); 
    }
}

int main()
{   
    pthread_mutex_init(&lock, NULL);
    
    sem_init(&agentSemafor, 0, 1);
    sem_init(&pusacDuvanSemafor, 0, 0);
    sem_init(&pusacRizleSemafor, 0, 0);
    sem_init(&pusacSibiceSemafor, 0, 0);
    
    pthread_create(&agent, NULL, &agent_f, NULL);
    pthread_create(&pusacDuvan, NULL, &pusac_duvan_f, NULL);
    pthread_create(&pusacRizle, NULL, &pusac_rizle_f, NULL);
    pthread_create(&pusacSibice, NULL, &pusac_sibice_f, NULL);
    
    pthread_join(agent, NULL);
    pthread_join(pusacDuvan, NULL);
    pthread_join(pusacRizle, NULL);
    pthread_join(pusacSibice, NULL);
    
    pthread_mutex_destroy(&lock);
    
    return 0;
}
