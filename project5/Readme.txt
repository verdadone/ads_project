project5中的代码包含：
用于PTA测试的代码：algorithm1.cpp	algorithm2.cpp
用于生成数据集的代码：datagen.cpp
用于测试生成数据集的代码: project5_test.cpp	algorithm1_test.cpp	         algorithm2_test.cpp	
(头文件介绍省略)	 

本project的代码均使用g++编译器，用vscode打开即可
如何使用代码：
1、验证代码是否编写准确：
在PTA上提交algorithm1.cpp或algorithm2.cpp即可
2、测试时间复杂度：
（1）生成数据
打开datagen.cpp，修改main中调用的DataGenerator即可生成测试数据，第一个参数为字符数，第二个参数为提交编码的同学的个数
该数据测试集生成99%的同学currentwpl与correctwpl一致，1%的随机（为了体现优化效果）
修改参数后，直接点击"run code"运行即可，最终会在当前文件目录下生成testcases_N_M.txt文件
（2）测试数据
打开project5_test.cpp、algorithm1_test.cpp、algorithm2_test.cpp
***注意:您要在algorithm1_test.cpp、algorithm2_test.cpp中的slow()与tree()函数中修改测试文件的路径，否则测试结果会出现异常
在终端输入g++ project5_test.cpp algorithm1_test.cpp algorithm2_test.cpp -o test进行编译
输入test运行
输出的第一行的时间为algorithm2运行的时间
输出的第二行的时间为algorithm1运行的时间

		