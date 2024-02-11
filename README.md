### Aros Projekat

Ovaj repozitorijum predstavlja projektni rad iz predmeta Arhitektura Računara i Operativni Sistemi. U pitanju je rešenje Cigarette Smokers problema iz **Little Book of Semaphores** knjige.

Rešenje je implementirano u programskom jeziku C, sa korišćenjem semafora i niti.

Tekst problema u originalu glasi:
```
Four threads are involved: an agent and three smokers. The smokers loop
forever, first waiting for ingredients, then making and smoking cigarettes. The
ingredients are tobacco, paper, and matches.

We assume that the agent has an infinite supply of all three ingredients, and
each smoker has an infinite supply of one of the ingredients; that is, one smoker
has matches, another has paper, and the third has tobacco.
The agent repeatedly chooses two different ingredients at random and makes
them available to the smokers. Depending on which ingredients are chosen, the
smoker with the complementary ingredient should pick up both resources and
proceed.

For example, if the agent puts out tobacco and paper, the smoker with the
matches should pick up both ingredients, make a cigarette, and then signal the
agent.

To explain the premise, the agent represents an operating system that allocates resources, and the smokers represent applications that need resources. 

The
problem is to make sure that if resources are available that would allow one more
applications to proceed, those applications should be woken up. Conversely, we
want to avoid waking an application if it cannot proceed.
```

### Pokretanje programa

Da bi se kod kompajlirao, potrebno je u terminalu pokrenuti Makefile koristeći komandu make:

```
  make
```

Nakon toga, u istom folderu biće kreiran fajl pod nazivom a.out. On se može pokrenuti sledećom komandom:

```
  ./a.out
``` 
