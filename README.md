# CuteSunny
GW CPP QT Project
1. 项目考察
	a. 大小（行数）：假如把魔兽cpp扩充为QT，估计1k~2k（基础代码500～1000+可视化500～1000）\
	b. 内容：\
		i. 需求、创意：\
			1) 校园生活、日常功能：日历日程、通知类、社交、课程、记账本（带分析）\
			2) 工业级的不考虑（常带硬件，但可利用基本PC硬件如麦克风，如dubler2\
		ii. 小游戏\
	c. QT特性：\
		i. 界面：\
			1) 交互，多功能，不能说打开就完事了\
			2) 集成，嵌入网页、桌面应用\
		ii. 数据流：来源、处理、输出？\
			1) 网页数据\
			2) 输入设备\
			3) 设备存储文件\
		iii. 信号槽（不懂）
2. 陈鹏的一个想法：pku covid-19 helper
	a. 设计目的：方便北大同学完成封校政策下的各项防疫任务，保障课程及其他校园生活的便利\
	b. 大致框架：\
		i. course\
			1) 类似course.pku.cn页面设计，子项为各学期各课程\
			2) 课程类中嵌入所有课程实际可能用到的通知交流软件，比如微信、teams；如不能嵌入则提供跳转按钮。主要接受上下课通知、自动打开classin或teams\
		ii. anti-covid-19\
			1) 自动检测邮箱、信息、微信等中防疫新通知（政策变更），并显示，可回复；并安排日程（如核酸检测）\
			2) 输入就医、就业、科研等需求，自动在出入校中提交申请，甚至包括承诺书等内容\
		iii. 其他\
			1) 生活方面：\
3. 开源
	a. PVZ 5k https://github.com/sunziping2016/Qt-PlantsVsZombies\
	b. 网易云 1k https://gitee.com/Morning_pkq/music-wwy/blob/master/MusicOfWYY/allmain.cpp![image](https://user-images.githubusercontent.com/65433575/167349891-4a0fb1e6-afc4-4ed4-8461-0b267c2485fb.png)\
