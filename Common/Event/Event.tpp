/*
 * --------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <benjamin.viguier@epitech.eu> wrote this file. As long as you retain this 
 * notice you can do whatever you want with this stuff. If we meet some day,
 * and you think this stuff is worth it, you can buy me a beer in
 * return Benjamin Viguier
 * --------------------------------------------------------------------------
 */

#pragma once

#include "Event.hpp"
#include <sstream>
#include <typeinfo>
#include <typeindex>
#include <vector>

namespace evt
{
	template <typename Ret, typename ...Args>
	inline std::string	Event::_extractTemplate()
	{
		std::ostringstream	stm;
		bool			first = false;

		stm << '(';
		for (auto &typeIdx: std::vector<std::type_index> {typeid(Args)...}) {
			if (first)
				stm << ", ";
			else
				first = true;
			stm << typeIdx.name();
		}
		stm << ") -> " << typeid(Ret).name();
		return (stm.str());
	}

	template <typename Ret, typename ...Args>
	const Event::EvtHdlDestr
	&Event::addHandler(typename FctSign<std::function<Ret(Args...)>>::type const &hdl) {
		EvtHdlBlock<Ret, Args...>	*blk = new EvtHdlBlock<Ret, Args...>();
		static std::string		tpl = _extractTemplate<Ret, Args...>();

		blk->hdl = hdl;
		_addToList(tpl, blk);
		return (blk->destructor);
	}

	template <typename Ret, typename ...Args>
	typename std::enable_if<(! std::is_same<Ret, void>::value), typename Event::FctSign<Ret>::ret>::type
	Event::fire(Args... args)
	{
		static std::string	tpl = _extractTemplate<Ret, Args...>();
		int			i = 0;
		auto			rList = _hdls.find(tpl);
		
		if (rList == _hdls.end())
			return std::make_shared<std::vector<Ret>>();

		auto	ret = std::make_shared<std::vector<Ret>>(rList->second.size());
		auto	&vec = *(ret.get());

		for (auto ptr : rList->second) {
			vec[i] = static_cast<EvtHdlBlock<Ret, Args...>*>(ptr)->hdl(args...);
			++i;
		}
		return ret;
	}

	template <typename Ret, typename ...Args>
	typename std::enable_if<std::is_same<Ret, void>::value, void>::type
	Event::fire(Args... args)
	{
		static std::string	tpl = _extractTemplate<void, Args...>();
		auto			rList = _hdls.find(tpl);
		
		if (rList == _hdls.end())
			return;

		for (auto ptr : rList->second) {
			static_cast<EvtHdlBlock<void, Args...>*>(ptr)->hdl(args...);
		}
	}

	template <typename ...Args>
	void	Event::fire(Args... args)
	{
		fire<void, Args...>(args...);
	}
}