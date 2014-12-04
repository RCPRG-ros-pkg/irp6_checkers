#include "ros/ros.h"
#include "irp6_checkers/Chessboard.h"
#include "Checkers.hpp"
#include <iostream>

class MoveDetermination
{
public:
	MoveDetermination();
	void callback(const irp6_checkers::Chessboard& msg);
private:
	ros::NodeHandle _nh;
	ros::Subscriber _chessboard_sub;
	Checkers::Chessboard _chessboard;
}; 

MoveDetermination::MoveDetermination()
{
	_chessboard_sub = _nh.subscribe("chessboard", 1000, &MoveDetermination::callback, this);
}

void MoveDetermination::callback(const irp6_checkers::Chessboard& msg)
{
	ROS_INFO("[MoveDetermination] ------> New data received.");
	_chessboard.clear();
	std::vector<irp6_checkers::Checker>::const_iterator end_it = msg.Chessboard.end();
	for(std::vector<irp6_checkers::Checker>::const_iterator it = msg.Chessboard.begin(); it != end_it; ++it)
	{
		Checkers::FieldValue type;
		switch((*it).type)
		{
		case irp6_checkers::Checker::PAWN_1:
			type = Checkers::PAWN_1;
			break;
		case irp6_checkers::Checker::PAWN_2:
			type = Checkers::PAWN_2;
			break;
		case irp6_checkers::Checker::KING_1:
			type = Checkers::KING_1;
			break;
		case irp6_checkers::Checker::KING_2:
			type = Checkers::KING_2;
			break;
		}
		_chessboard.addChecker(Checkers::Position((*it).x,(*it).y), type);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "move_determination");
	MoveDetermination determination;
	ros::spin();
	return 0;
}
