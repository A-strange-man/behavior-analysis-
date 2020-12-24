#pragma once

/**
 * 大学男生幸福指数测评和优化建议系统
 * 
 * 系统根据用户输入的 时间-行为 表反馈给用户一个幸福指数
 * 并且根据用户的情况反馈给用户阶段化的 时间-行为 的调整方案
 * 从而帮助用户体高幸福指数
 * 
 * 
 * 输入字段：
 * 娱乐（追剧，游戏，音乐，电影。。。。）
 * 学习（读书，写作业。。。。）
 * 运动（球类，跑步。。。）
 * 睡眠
 * 其它（恋爱，吃饭。。。。）
 *
 * 输入字段的单位确定：hours（行为持续时间段）
 *
 * 时间最佳组合：6(学习) + 2(运动) + 4(娱乐) + 4(其它) + 8(睡眠) = 24
 * 最佳组合得分 >= 90 
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Behavior_analysis
{
public:
	Behavior_analysis();

	//用户输入数据的接口
	void userInput();

	//用户得分输出，初始化 行为-时间 变量
	void output();

private:
	// 分析函数，自动优化用户行为
	void analysis();

	// 更新 超越集 和 缺省集
	void update_more_less();

	// 判断超越集和缺省集是否都为空
	bool isNULL_more_less() const;

	// 更新 用户-行为 变量
	void update_behavior_score();

	// 根据 行为-时间 变量 获取用户幸福指数得分，存入source_
	void get_source();

	//输出 行为-时间表
	void output_behavior_time();

	// 定义标准行为
	void definition_of_happiness();

	// 输出行为得分和幸福指数
	void print_score();

	double entertainment_; //娱乐行为持续时间
	double study_;         //学习行为持续时间
	double motion_;        //运动行为持续时间
	double others_;        //其它行为持续时间
	double sleep_;         //睡眠行为持续时间

	// <begin, end, define>---开始 / 结束 / 得分
	typedef std::vector<std::vector<double>> vec;
	vec study_definition_;          //学习 时间-分数 集
	vec motion_definition_;         //运动 时间-分数 集
	vec entertainment_definition_;  //娱乐 时间-分数 集
	vec sleep_definition_;          //睡眠 时间-分时 集
	vec other_definition_;          //其它 时间-分数 集

	std::vector<double> usrInfo_;    //用户数据  学习--运动--娱乐--睡眠--其它
	std::unordered_map<std::string, double> source_;	//存储用户的得分

	// 超越集/缺省集 的存储对象
	struct st
	{
		std::string behavior;
		double count;
	};

	// 超越集
	std::vector<st> more_;	//存正数count
	// 缺省集
	std::vector<st> less_;	//存负数count
};