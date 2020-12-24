#include "behavior_analysis.h"

#define BEST_STUDY_BEGIN            5.0
#define BEST_STUDY_END              6.0
#define BEST_STUDY_SOURCE           30.0
#define STUDY_NUM 11

#define BEST_MONTION_BEGIN          1.5
#define BEST_MONTION_END            2.0
#define BEST_MONTION_SOURCE         20.0
#define MONTION_NUM 8

#define BEST_ENTERTAINMENT_BEGIN    3.0
#define BEST_ENTERTAINMENT_END      4.0
#define BEST_ENTERTAINMENT_SOURCE   15.0
#define ENTERTAINMENT_NUM 8

#define BEST_SLEEP_BEGIN            6.0
#define BEST_SLEEP_END              8.0
#define BEST_SLEEP_SOURCE           20.0
#define SLEEP_NUM 7

#define BEST_OTHERS_BEGIN           3.0
#define BEST_OTHERS_END             4.0
#define BEST_OTHERS_SOURCE          15.0
#define OTHERS_NUM 8

// 定义最佳时间安排
#define BEST_STUDY_TIME 6.0
#define BEST_MONTION_TIME 2.0
#define BEST_ENTERTAINMENT_TIME 4.0
#define BEST_SLEEP_TIME 8.0
#define BEST_OTHER_TIME 4.0

Behavior_analysis::Behavior_analysis()
{
	// 初始化
	definition_of_happiness();	// 初始化标准幸福定义
}

void Behavior_analysis::userInput()
{
	double var;
	std::cout << "请输入你一天中用于学习的时间(按小时计算，可以是小数：)";
	std::cin >> var;
	study_ = var;
	usrInfo_.push_back(var);
	std::cout << std::endl;

	std::cout << "请输入你一天中用于运动的时间(按小时计算，可以是小数：)";
	std::cin >> var;
	motion_ = var;
	usrInfo_.push_back(var);
	std::cout << std::endl;

	std::cout << "请输入你一天中用于娱乐的时间(按小时计算，可以是小数：)";
	std::cin >> var;
	entertainment_ = var;
	usrInfo_.push_back(var);
	std::cout << std::endl;

	std::cout << "请输入你一天中用于睡眠的时间(按小时计算，可以是小数：)";
	std::cin >> var;
	sleep_ = var;
	usrInfo_.push_back(var);
	std::cout << std::endl;

	std::cout << "请输入你一天中用于其它的时间(按小时计算，可以是小数：)";
	std::cin >> var;
	others_ = var;
	usrInfo_.push_back(var);
	std::cout << std::endl;

	// 根据用户输入 进行初始化
	get_source();				// 获取各行为得分
	update_more_less();			// 第一次更新 超越集 和 缺省集
}

void Behavior_analysis::print_score()
{
	double sum = 0;
	for (auto& x : source_)
	{
		std::cout << x.first << " 得分 : " << x.second << std::endl;
		sum += x.second;
	}
	std::cout << "幸福指数：" << sum << std::endl;
}

// 现在用于测试
void Behavior_analysis::output()
{
	// 输出用户第一次的输入数据，给用户一个幸福指数分析反馈
	print_score();

	//生成新的 行为-时间 表
	analysis();
}

void Behavior_analysis::analysis()
{
	// 生成三次时间更新
	//for (int i = 0; i < 5; ++i)
	//{
	//	if (!isNULL_more_less())
	//	{
	//		// 新的时间分配 -> 更新用户得分 -> 更新用户 行为-时间表 -> 更新超越集和缺省集 
	//		update_behavior_score();
	//	}
	//}
    std::cout << "根据你的行为时间表，我们为提高你的幸福指数做了阶段化的行为时间安排：" << std::endl << std::endl;
    int cnt = 1;
	while (!isNULL_more_less())
	{
        std::cout << std::endl << "第" << cnt++ << "阶段安排：" << std::endl; 
        // 新的时间分配 -> 更新用户得分 -> 更新用户 行为-时间表 -> 更新超越集和缺省集
		update_behavior_score();
	}
}

// 更新 超越集 和 缺省集
void Behavior_analysis::update_more_less()
{
	if (!more_.empty())
		more_.clear();
	if (!less_.empty())
		less_.clear();

	// 学习
	if (study_ > BEST_STUDY_TIME || study_ < BEST_STUDY_TIME)
	{
		st s;
		s.behavior = "学习";
		s.count = study_ - BEST_STUDY_TIME;
		if (s.count > 0)
		{
			more_.push_back(s);
		}
		else if (s.count < 0)
		{
			less_.push_back(s);
		}
	}

	// 运动
	if (motion_ > BEST_MONTION_TIME || motion_ < BEST_MONTION_TIME)
	{
		st s;
		s.behavior = "运动";
		s.count = motion_ - BEST_MONTION_TIME;
		if (s.count > 0)
		{
			more_.push_back(s);
		}
		else if (s.count < 0)
		{
			less_.push_back(s);
		}
	}

	// 娱乐
	if (entertainment_ > BEST_ENTERTAINMENT_TIME || entertainment_ < BEST_ENTERTAINMENT_TIME)
	{
		st s;
		s.behavior = "娱乐";
		s.count = entertainment_ - BEST_ENTERTAINMENT_TIME;
		if (s.count > 0)
		{
			more_.push_back(s);
		}
		else if (s.count < 0)
		{
			less_.push_back(s);
		}
	}

	// 睡眠
	if (sleep_ > BEST_SLEEP_TIME || sleep_ < BEST_SLEEP_TIME)
	{
		st s;
		s.behavior = "睡眠";
		s.count = sleep_ - BEST_SLEEP_TIME;
		if (s.count > 0)
		{
			more_.push_back(s);
		}
		else if (s.count < 0)
		{
			less_.push_back(s);
		}
	}

	//其它
	if (others_ > BEST_OTHER_TIME || others_ < BEST_OTHER_TIME)
	{
		st s;
		s.behavior = "其它";
		s.count = others_ - BEST_OTHER_TIME;
		if (s.count > 0)
		{
			more_.push_back(s);
		}
		else if (s.count < 0)
		{
			less_.push_back(s);
		}
	}
}

// 判断超越集和缺省集是否都为空
bool Behavior_analysis::isNULL_more_less() const
{
	if (more_.empty() && less_.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 更新 用户-行为 变量
void Behavior_analysis::update_behavior_score()
{
	double more_temp = 0;
	double less_temp = 0;

	if (!isNULL_more_less())	//超越集和缺省集不为空，更新 用户-行为 变量
	{
		// 超越集
		for (int j = 0; j < more_.size(); ++j)
		{
			if (more_[j].behavior == "学习")
			{
				int study_iter = 0;	//学习时间的指针
				for (int i = 0; i < STUDY_NUM; ++i)
				{
					if (study_ >= study_definition_[i][0] && study_ <= study_definition_[i][1])
					{
						study_iter = i;
						break;
					}
				}
				--study_iter;	//学习指针前移
				double new_study_time = study_definition_[study_iter][1];	// 获取新的学习时间
				double t = study_ - new_study_time;	//获取时间差
				more_temp += t;		// 时间差存入more_temp;
				study_ = new_study_time;	//更新学习时间
			}

			if (more_[j].behavior == "运动")
			{
				int motion_iter = 0;
				for (int i = 0; i < MONTION_NUM; ++i)
				{
					if (motion_ >= motion_definition_[i][0] && motion_ <= motion_definition_[i][1])
					{
						motion_iter = i;
						break;
					}
				}
				--motion_iter;
				double new_motion_time = motion_definition_[motion_iter][1];
				double t = motion_ - new_motion_time;
				more_temp += t;
				motion_ = new_motion_time;
			}

			if (more_[j].behavior == "娱乐")
			{
				int entertainment_iter = 0;
				for (int i = 0; i < ENTERTAINMENT_NUM; ++i)
				{
					if (entertainment_ >= entertainment_definition_[i][0] && entertainment_ <= entertainment_definition_[i][1])
					{
						entertainment_iter = i;
						break;
					}
				}
				--entertainment_iter;
				double new_entertainment_time = entertainment_definition_[entertainment_iter][1];
				double t = entertainment_ - new_entertainment_time;
				more_temp += t;
				entertainment_ = new_entertainment_time;
			}

			if (more_[j].behavior == "睡眠")
			{
				int sleep_iter = 0;
				for (int i = 0; i < SLEEP_NUM; ++i)
				{
					if (sleep_ >= sleep_definition_[i][0] && sleep_ <= sleep_definition_[i][1])
					{
						sleep_iter = i;
						break;
					}
				}
				--sleep_iter;
				double new_sleep_time = sleep_definition_[sleep_iter][1];
				double t = sleep_ - new_sleep_time;
				more_temp += t;
				sleep_ = new_sleep_time;
			}

			if (more_[j].behavior == "其它")
			{
				int other_iter = 0;
				for (int i = 0; i < OTHERS_NUM; ++i)
				{
					if (others_ >= other_definition_[i][0] && others_ <= other_definition_[i][1])
					{
						other_iter = i;
						break;
					}
				}
				--other_iter;
				double new_other_time = other_definition_[other_iter][1];
				double t = others_ - new_other_time;
				more_temp += t;
				others_ = new_other_time;
			}
		} //end 超越集 -> more_temp

		double count_all = 0.0;
		for (int j = 0; j < less_.size(); ++j)
		{
			count_all += less_[j].count;
		}

		// 将超越集多出的时间 more_temp 分配给缺省集
		for (int j = 0; j < less_.size(); ++j)	
		{
			double t = more_temp * (less_[j].count / count_all);	//时间分配比例
			
			if (less_[j].behavior == "学习" && study_ < BEST_STUDY_TIME)
			{
				if (t > 0)
				{
					study_ += t;
				}
			}
			else if (less_[j].behavior == "运动" && motion_ < BEST_MONTION_TIME)
			{
				if (t > 0)
				{
					motion_ += t;
				}
			}
			else if (less_[j].behavior == "娱乐" && entertainment_ < BEST_ENTERTAINMENT_TIME)
			{
				if (t > 0)
				{
					entertainment_ += t;
				}
			}
			else if (less_[j].behavior == "睡眠" && sleep_ < BEST_SLEEP_TIME)
			{
				if (t > 0)
				{
					sleep_ += t;
				}
			}
			else if (less_[j].behavior == "其它" && others_ < BEST_OTHER_TIME)
			{
				if (t > 0)
				{
					others_ += t;
				}
			}
		}

		// 更新用户得分source_
		get_source();

		std::cout << "---------------------------------------" << std::endl;
		//输出新 行为-时间表
		output_behavior_time();
		//输出健康指数
		print_score();

		//更新 超越集 和 缺省集合
		update_more_less();
	}
}

// 数据量不大，直接采用 遍历-匹配 的方法
void Behavior_analysis::get_source()
{
	double s_sleep;
	double s_motion;
	double s_study;
	double s_entertainment;
	double s_other;

	// 学习时间检测
	if (study_ > BEST_STUDY_BEGIN && study_ <= BEST_STUDY_END)
	{
		// std::cout << "你的学习时间安排非常棒" << std::endl;
		s_study = BEST_SLEEP_SOURCE;
	}
	else
	{
		for (int i = 0; i < STUDY_NUM; ++i)
		{
			if (study_ > study_definition_[i][0] && study_ <= study_definition_[i][1])
			{
				s_study = study_definition_[i][2];
				break;
			}
		}
	}

	// 运动时间检测
	if (motion_ > BEST_MONTION_BEGIN && motion_ <= BEST_MONTION_END)
	{
		// std::cout << "你的运动时间安排非常棒" << std::endl;
		s_motion = BEST_MONTION_SOURCE;
	}
	else
	{
		for (int i = 0; i < MONTION_NUM; ++i)
		{
			if (motion_ > motion_definition_[i][0] && motion_ <= motion_definition_[i][1])
			{
				s_motion = motion_definition_[i][2];
				break;
			}
		}
	}

	// 娱乐时间检测
	if (entertainment_ > BEST_ENTERTAINMENT_BEGIN && entertainment_ <= BEST_ENTERTAINMENT_END)
	{
		// std::cout << "你的娱乐时间安排的非常棒" << std::endl;
		s_entertainment = BEST_ENTERTAINMENT_SOURCE;
	}
	else
	{
		for (int i = 0; i < ENTERTAINMENT_NUM; ++i)
		{
			if (entertainment_ > entertainment_definition_[i][0] && entertainment_ <= entertainment_definition_[i][1])
			{
				s_entertainment = entertainment_definition_[i][2];
				break;
			}
		}
	}

	// 睡眠时间检测
	if (sleep_ > BEST_SLEEP_BEGIN && sleep_ <= BEST_SLEEP_END)
	{
		// std::cout << "你的睡眠时间安排的非常棒" << std::endl;
		s_sleep = BEST_SLEEP_SOURCE;
	}
	else
	{
		for (int i = 0; i < SLEEP_NUM; ++i)
		{
			if (sleep_ > sleep_definition_[i][0] && sleep_ <= sleep_definition_[i][1])
			{
				s_sleep = sleep_definition_[i][2];
				break;
			}
		}
	}

	// 其它时间检测
	if (others_ > BEST_OTHERS_BEGIN && others_ <= BEST_OTHERS_END)
	{
		// std::cout << "你的其它时间安排的非常棒" << std::endl;
		s_other = BEST_OTHERS_SOURCE;
	}
	else
	{
		for (int i = 0; i < OTHERS_NUM; ++i)
		{
			if (others_ > other_definition_[i][0] && others_ <= other_definition_[i][1])
			{
				s_other = other_definition_[i][2];
				break;
			}
		}
	}

	// 写入得分情况
	source_.clear();	//清空source_
	source_.insert(std::pair<std::string, double>("学习", s_study));
	source_.insert(std::pair<std::string, double>("运动", s_motion));
	source_.insert(std::pair<std::string, double>("娱乐", s_entertainment));
	source_.insert(std::pair<std::string, double>("睡眠", s_sleep));
	source_.insert(std::pair<std::string, double>("其它", s_other));
}

//输出 行为-时间表
void Behavior_analysis::output_behavior_time()
{
	std::cout << std::endl;
	std::cout << "新的时间安排：" << std::endl;
	std::cout << "学习时间安排：" << study_  << " h" << std::endl;
	std::cout << "运动时间安排: " << motion_ << " h" << std::endl;
	std::cout << "娱乐时间安排: " << entertainment_ << " h" << std::endl;
	std::cout << "睡眠时间安排：" << sleep_ << " h" << std::endl;
	std::cout << "其它时间安排：" << others_ << " h" << std::endl;
	std::cout << std::endl;
}

/**
 * 大学男生快乐生活的标准（经过调查得到）
 * 这里按照分段将数据写死，因为没有变动的任何必要
 */
void Behavior_analysis::definition_of_happiness()
{
	// 学习
	study_definition_.push_back(std::vector<double>{0, 1, -20});
	study_definition_.push_back(std::vector<double>{1, 2, -10});
	study_definition_.push_back(std::vector<double>{2, 3, 0});
	study_definition_.push_back(std::vector<double>{3, 4, 10});
	study_definition_.push_back(std::vector<double>{4, 5, 20});
	study_definition_.push_back(std::vector<double>{5, 6, 30});
	study_definition_.push_back(std::vector<double>{6, 7, 20});
	study_definition_.push_back(std::vector<double>{7, 8, 10});
	study_definition_.push_back(std::vector<double>{8, 9, 0});
	study_definition_.push_back(std::vector<double>{9, 10, -10});
	study_definition_.push_back(std::vector<double>{10, 24, -20});
	// 运动
	motion_definition_.push_back(std::vector<double>{0, 0.5, 5});
	motion_definition_.push_back(std::vector<double>{0.5, 1, 10});
	motion_definition_.push_back(std::vector<double>{1, 1.5, 15});
	motion_definition_.push_back(std::vector<double>{1.5, 2, 20});
	motion_definition_.push_back(std::vector<double>{2, 2.5, 15});
	motion_definition_.push_back(std::vector<double>{2.5, 3, 10});
	motion_definition_.push_back(std::vector<double>{3, 3.5, 5});
	motion_definition_.push_back(std::vector<double>{3.5, 24, 0});
	// 娱乐
	entertainment_definition_.push_back(std::vector<double>{0, 1, 0});
	entertainment_definition_.push_back(std::vector<double>{1, 2, 5});
	entertainment_definition_.push_back(std::vector<double>{2, 3, 10});
	entertainment_definition_.push_back(std::vector<double>{3, 4, 15});
	entertainment_definition_.push_back(std::vector<double>{4, 5, 10});
	entertainment_definition_.push_back(std::vector<double>{5, 6, 5});
	entertainment_definition_.push_back(std::vector<double>{6, 7, 0});
	entertainment_definition_.push_back(std::vector<double>{7, 24, -5});
	// 睡眠
	sleep_definition_.push_back(std::vector<double>{0, 5, 5});
	sleep_definition_.push_back(std::vector<double>{5, 6, 5});
	sleep_definition_.push_back(std::vector<double>{6, 7, 20});
	sleep_definition_.push_back(std::vector<double>{7, 8, 20});
	sleep_definition_.push_back(std::vector<double>{8, 9, 5});
	sleep_definition_.push_back(std::vector<double>{9, 10, 5});
	sleep_definition_.push_back(std::vector<double>{10, 24, 5});
	// 其它
	other_definition_.push_back(std::vector<double>{0, 1, 0});
	other_definition_.push_back(std::vector<double>{1, 2, 5});
	other_definition_.push_back(std::vector<double>{2, 3, 10});
	other_definition_.push_back(std::vector<double>{3, 4, 15});
	other_definition_.push_back(std::vector<double>{4, 5, 10});
	other_definition_.push_back(std::vector<double>{5, 6, 5});
	other_definition_.push_back(std::vector<double>{6, 7, 0});
	other_definition_.push_back(std::vector<double>{7, 24, -5});
}

