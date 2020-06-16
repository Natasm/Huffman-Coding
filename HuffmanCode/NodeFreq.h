#ifndef NODEFREQ_H_INCLUDED
#define NODEFREQ_H_INCLUDED

typedef struct nodefreq* NodeFreq;

NodeFreq newNodeFreq(char c, int freq);

char getKeyNodeFreq(NodeFreq n);

int getContentNodeFreq(NodeFreq n);

NodeFreq addContentNodeFreq(NodeFreq n, int add);

#endif // NODEFREQ_H_INCLUDED
