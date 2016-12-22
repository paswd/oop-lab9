#include <iostream>
#include "square.h"
#include "trapeze.h"
#include "rectangle.h"
#include "TStack.h"
#include "n-tree.h"
#include <future>
#include <functional>
#include <random>
#include <thread>
#include "geometry.h"

using namespace std;

int main(void)
{
	TStack<Figure> stack_figure;
	typedef std::function<void (void) > command;
	NTree <command> ntree_cmd;
	command cmd_insert_rectangle = [&]() {
		std::cout << "Command: Create rectangle" << std::endl;
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, 1000);
		for (int i = 0; i < 10; i++) {
			Position pos;
			pos.x = distribution(generator);
			pos.y = distribution(generator);
			int side_a = distribution(generator);
			int side_b = distribution(generator);
			stack_figure.push(new Rectangle(pos, side_a, side_b));
		}
	};
	command cmd_insert_square = [&]() {
		std::cout << "Command: Create square" << std::endl;
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, 1000);
		for (int i = 0; i < 10; i++) {
			int side = distribution(generator);
			Position pos;
			pos.x = distribution(generator);
			pos.y = distribution(generator);
			stack_figure.push(new FSquare(pos, side));
		}
	};
	command cmd_insert_trapeze = [&]() {
		std::cout << "Command: Create trapeze" << std::endl;
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, 1000);
		for (int i = 0; i < 10; i++) {
			Position pos1, pos2;
			pos1.x = distribution(generator);
			pos1.y = distribution(generator);
			pos2.x = distribution(generator);
			pos2.y = distribution(generator);
			int side_a = distribution(generator);
			int side_b = distribution(generator);
			stack_figure.push(new Trapeze(pos1, pos2, side_a, side_b));
		}
	};
	command cmd_print = [&]() {
		std::cout << "Command: Print stack" << std::endl;
		std::cout << stack_figure;
	};
	command cmd_delete = [&]() {
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, 1000);
		int limit = distribution(generator);
		std::cout << "Command: Deleting elements under stack less than <" << limit << ">" << std::endl;


		TStack<Figure> stack_tmp;
		while(!stack_figure.empty()) {
			//stack_tmp.push(stack_figure.pop_last());
			std::shared_ptr<Figure> obj = stack_figure.pop();
			if (obj->Square() >= (double) limit) {
				stack_tmp.push(obj);
			}
		}
		while(!stack_tmp.empty()) {
			stack_figure.push(stack_tmp.pop());
		}
	};
	ntree_cmd.Push(std::shared_ptr<command> (&cmd_print, [](command*) {
	})); // using custom deleter
	ntree_cmd.Push(std::shared_ptr<command> (&cmd_delete, [](command*) {
	})); // using custom deleter
	ntree_cmd.Push(std::shared_ptr<command> (&cmd_print, [](command*) {
	})); // using custom deleter
	ntree_cmd.Push(std::shared_ptr<command> (&cmd_insert_rectangle, [](command*) {
	})); // using custom deleter
	ntree_cmd.Push(std::shared_ptr<command> (&cmd_insert_square, [](command*) {
	})); // using custom deleter
	ntree_cmd.Push(std::shared_ptr<command> (&cmd_insert_trapeze, [](command*) {
	})); // using custom deleter
	while (!ntree_cmd.IsEmpty()) {
		std::shared_ptr<command> cmd = ntree_cmd.Pop();
		std::future<void> ft = std::async(*cmd);
		ft.get();
	}

 return 0;
}
