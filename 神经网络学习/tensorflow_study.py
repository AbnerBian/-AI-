# -*- coding: utf-8 -*-
"""
Created on Wed Dec 13 21:07:43 2017

@author: Abner Bian
"""

import tensorflow as tf


"""
下面这段代码产生了两个计算图，每个计算图中定义了一个名字为"v"的变量。
在计算图g1中，将v初始化为0，在计算图g2中，将v初始化为1.可以看到当运行不同计算
图时，变量v的值也是不一样的。tensorflow中的计算图不仅仅可以用来隔离张量和计算，他还
提供了管理张量和计算的机制
"""
"""
#graph生成新的计算图
g1=tf.Graph()
with g1.as_default():
    #在计算图g1中定义变量"v",并设置初始值为0
    v=tf.get_variable("v",initializer=tf.zeros_initializer,shape=[1])

g2=tf.Graph()
with g2.as_default():
    #在计算图g2中定义变量"v",并设置初始值为1
    v=tf.get_variable("v",initializer=tf.ones_initializer,shape=[1])
    
#在计算图g1中读取变量"v"的取值
with tf.Session(graph=g1) as sess:
    tf.initialize_all_variables().run()
    with tf.variable_scope("",reuse=True):
        #在计算图g1中，变量"v"的取值应该为0，所以下面这行会输出[0,]
        print(sess.run(tf.get_variable("v")))
#在计算图g2中读取变量"v"的取值
with tf.Session(graph=g2) as sess:
    tf.initialize_all_variables().run()
    with tf.variable_scope("",reuse=True):
        #在计算图g2中，变量"v"的取值应该为1，所以下面这行会输出[1.]
        print(sess.run(tf.get_variable("v")))

"""


"""
张量的概念
"""
'''
#tf.constant是一个计算，这个计算的结果为一个张量，保存在变量a中
a=tf.constant([1.0,2.0],name="a")
b=tf.constant([2.0,3.0],name="b")
result=tf.add(a,b,name="add")
sess=tf.Session()
#将生成的函数注册为默认会话
'''
"""
sess=tf.Session()
with sess.as_default():
    print(sess.run(result))
"""    
'''
'''
"""
#自动将生成的函数注册为默认会话
sess=tf.InteractiveSession()
print(result.eval())
sess.close()
'''
"""
"""
#声明w1,w2两个变量，这里通过seed参数设定了随机种子
#这样可以保证每次运行得到的结果是一样的
w1=tf.Variable(tf.random_normal([2,3],stddev=1,seed=1))
w2=tf.Variable(tf.random_normal([3,1],stddev=1,seed=1))
#暂时将输入的特征向量定义为参数，注意这里x是一个1*2的矩阵
x=tf.constant([[0.7,0.9]])

#通过前向传播算法获得神经网络的输出
a=tf.matmul(x,w1)
y=tf.matmul(a,w2)

sess=tf.Session()
#因为w1和w2都还没有运行初始化过程,下面两行分别初始化了w1和w2两个变量
#sess.run(w1.initializer)#初始化w1
#sess.run(w2.initializer)#初始化w2
#输出[[3.95757794]]
init_op=tf.global_variables_initializer()
sess.run(init_op)
print(sess.run(y))
sess.close()
"""
w1=tf.Variable(tf.random_normal([2,3],stddev=1))
w2=tf.Variable(tf.random_normal([3,1],stddev=1))

#定义placeholder作为存放输入数据的地方，这里的维度也不一定要定义
#但是如果维度是确定的，那么给出维度可以降低出错的概率
#一个样例
"""
x=tf.placeholder(tf.float32,shape=(1,2),name="input")
a=tf.matmul(x,w1)
y=tf.matmul(a,w2)

sess=tf.Session()
init_op=tf.global_variables_initializer()
sess.run(init_op)
print(sess.run(y,feed_dict={x:[[0.7,0.9]]}))
"""
#多个样例

x=tf.placeholder(tf.float32,shape=(3,2),name="input")
a=tf.matmul(x,w1)
y=tf.matmul(a,w2)
sess=tf.Session()
init_op=tf.global_variables_initializer()
sess.run(init_op)
#运行时提供了三个样例数据
print(sess.run(y,feed_dict={x:[[0.7,0.9],[0.1,0.4],[0.5,0.8]]}))
































