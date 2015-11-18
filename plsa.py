# -*- coding: utf-8 -*-
import re

M = 2246 #Doc
N = 10473 #Word
K = 5 #Topic
re_nIdNum = re.compile(r'^(\d+)\:(\d+)$')

nDocWord = [[0 for j in range(N)] for i in range(M)]
pDocTopic = [[1.0/K for j in range(K)] for i in range(M)]
pTopicWord = [[1.0/N for j in range(N)]for i in range(K)]
qTopicDocWord = [[[0.0 for k in range(N)] for j in range(M)] for i in range(K)] 

def loadData():
    with open('ap.dat','r') as f:
        j = 0
        for line in f.readlines():
            words = line.split(' ')
            i = 1
            while i <= int(words[0]):
                wordId = re_nIdNum.match(words[i]).group(1)
                wordNum = re_nIdNum.match(words[i]).group(2)
                nDocWord[j][int(wordId)] = int(wordNum)
                i = i + 1
            j = j + 1

def initialize():
    print 'plsa initialized'
    print

def calPDocTopic():
    print 'calPDocTopic:'
    sum1 = 0.0
    sum2 = 0.0
    for i in range(M):
        for k in range(K):
            for j in range(N):
                sum1 = sum1 + nDocWord[i][j] * qTopicDocWord[k][i][j]
                sum2 = sum2 + nDocWord[i][j] * qTopicDocWord[k][i][j]
            pDocTopic[i][k] = sum1
            sum1 = 0.0
        for k in range(K):
            pDocTopic[i][k] = pDocTopic[i][k] / sum2
        sum2 = 0.0
        if i%1000 == 0:
            print 'Document', i
    print
            
def calPTopicWord():
    print 'calPTopicWord:'
    sum1 = 0.0
    sum2 = 0.0
    for k in range(K):
        for j in range(N):
            for i in range(M):
                sum1 = sum1 + nDocWord[i][j] * qTopicDocWord[k][i][j]
                sum2 = sum2 + nDocWord[i][j] * qTopicDocWord[k][i][j]
            pTopicWord[k][j] = sum1
            sum1 = 0.0
        for j in range(N):
            pTopicWord[k][j] = pTopicWord[k][j] / sum2
        sum2 = 0.0
        if k%3 == 0:
            print 'Topic', k
    print
        
def calQTopicDocWord():
    print 'calQTopicDocWord:'
    sum1 = 0.0
    for i in range(M):
        for j in range(N):
            for k in range(K):
                sum1 = sum1 + pTopicWord[k][j] * pDocTopic[i][k]
            for k in range(K):
                qTopicDocWord[k][i][j] = pTopicWord[k][j] * pDocTopic[i][k] / sum1
            sum1 = 0.0
        if i%1000 == 0:
            print 'Document', i
    print

def printResult():
    for k in range(K):
        for j in range(N):
            print pTopicWord[k][j],
        print
        
def em():
    initialize()
    for i in range(3):
        print 'iteration', i
        calQTopicDocWord()
        calPDocTopic()
        calPTopicWord()
        
loadData()
em()
printResult()