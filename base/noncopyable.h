/*************************************************************************
    > File Name: ./base/noncopyable.h
    > Author: wtmlonman
    > Mail: wtmlon@foxmail.com 
    > Created Time: Saturday, March 21, 2020 PM04:09:51 HKT
 ************************************************************************/
#pragma once

using namespace std;
class noncopyable {
	protected:
		noncopyable() {

		}
		~noncopyable() {

		}

	private:
		noncopyable(const noncopyable&);
		const noncopyable& operator=(const noncopyable&);
};
