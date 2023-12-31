#include "kernel/types.h"
#include "user/user.h"
#include "user/threads.h"

#define NULL 0

void s2(int signo)
{
    int i = 0;
    while(1) {
        if(signo) printf(" (#) \n");
        else printf(" (@) \n");
        i++;
        if (i == 3) {
            thread_exit();
        }
        thread_yield();
    }    
}

void s1(int signo)
{
    int i = 0;
    while(1) {
        if(signo) printf(" (&) \n");
        else printf(" (*) \n");
        i++;
        if (i == 3) {
            return;
        }
        thread_yield();
    }    
}

void f5(void *arg)
{
    int i = 0;
    while (1) {
        printf(" ( ) \n");
        if(++i == 1){
            thread_exit();
        }
        thread_yield();
    }
}

void f4(void *arg)
{
    int i = 0;

    while (1) {
        printf(" (.) \n");
        struct thread *t5 = thread_create(f5, NULL);
        thread_add_runqueue(t5);
        thread_kill(t5, 1);
        
        if(++i == 2){
            thread_exit();
        }
        thread_yield();
    }
}

void f3(void *arg)
{
    int i = 0;
    while (1) {
        printf(" (-) \n");
        if(i == 0){
            struct thread *t4 = thread_create(f4, NULL);
            thread_add_runqueue(t4);
            thread_kill(t4, 1);
        }
        else if(i == 1){
            thread_register_handler(0, s1);
            struct thread *t4 = thread_create(f4, NULL);
            thread_add_runqueue(t4);
            thread_kill(t4, 0);
        }
        else{
            thread_register_handler(0, s2);
            struct thread *t4 = thread_create(f4, NULL);
            thread_add_runqueue(t4);
            thread_kill(t4, 0);
        }
        if(++i == 3){
            thread_exit();
        }
        thread_yield();
    }
}

void f2(void *arg)
{
    int i = 0;
    while(1) {
        printf(" (o) \n");
        struct thread *t3 = thread_create(f3, NULL);
        thread_add_runqueue(t3);
        if (++i == 1) {
            thread_exit();
        }
        thread_yield();
    }
}

void f1(void *arg)
{
    int i = 0;
    
    while(1) {
        printf("-( )-\n");
        struct thread *t2 = thread_create(f2, NULL);
        thread_add_runqueue(t2);
        if (++i == 2) {
            return;
        }
        thread_yield();
    }
}

int main(int argc, char **argv)
{
    printf("mp1-part2-6\n");
    printf(" \\ / \n");
    struct thread *t1 = thread_create(f1, NULL);
    thread_add_runqueue(t1);
    thread_start_threading();
    printf(" / \\ \n");
    printf("\nexited\n");
    exit(0);
}
