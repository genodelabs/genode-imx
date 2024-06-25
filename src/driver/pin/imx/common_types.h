/*
 * \brief  Common pin driver types
 * \author Norman Feske
 * \date   2021-04-14
 */

#ifndef _COMMON_TYPES_H_
#define _COMMON_TYPES_H_

/* Genode includes */
#include <util/xml_node.h>
#include <base/log.h>

namespace Pin_driver {

	using namespace Genode;

	struct Name;
	struct Index;
	struct Function;
	struct Pull;
	struct Irq_trigger;
	struct Attr;
}


struct Pin_driver::Name
{
	using String = Genode::String<32>;

	String string;

	static Name from_xml(Xml_node const &node)
	{
		return { node.attribute_value("name", String()) };
	}

	bool operator == (Name const &other) const { return other.string == string; }
};


/**
 * Pin index within bank
 */
struct Pin_driver::Index
{
	unsigned value;

	class Invalid : Exception { };

	static Index from_xml(Xml_node node)
	{
		if (!node.has_attribute("index")) {
			warning("pin declaration lacks 'index' attribute: ", node);
			throw Invalid();
		}
		return Index { node.attribute_value("index", 0u) };
	}
};


struct Pin_driver::Function
{
	enum Value { INPUT = 0, OUTPUT = 1 } value;

	Function() = delete;
	Function(Value value) : value(value) { }

	class Invalid : Exception { };

	static Function from_xml(Xml_node node)
	{
		if (node.has_type("in"))
			return Function { INPUT };

		if (node.has_type("out"))
			return Function { OUTPUT };

		throw Invalid();
	};

	Pin::Direction direction() const
	{
		return (value == OUTPUT) ? Pin::Direction::OUT : Pin::Direction::IN;
	}

	void print(Output &out) const
	{
		switch (value)
		{
			case INPUT:
				Genode::print(out, "INPUT");
				break;
			case OUTPUT:
				Genode::print(out, "OUTPUT");
				break;
			default:
				Genode::print(out, (unsigned)value);
				break;
		}
	}
};


struct Pin_driver::Pull
{
	enum Value { DISABLE = 0, UP = 1, DOWN = 2 } value;

	class Invalid : Exception { };

	static Pull from_xml(Xml_node node)
	{
		if (node.has_attribute("pull"))
			warning("pull-up/pull-down not supported, must be done via IOMUXC");
		return Pull { DISABLE };
	};
};


struct Pin_driver::Irq_trigger
{
	enum Config { LOW = 0, HIGH = 1, RISING = 2, FALLING = 3 } config;
	enum Edge_select { OFF = 0, EDGES = 1 } edges;

	class Invalid : Exception { };

	static Irq_trigger from_xml(Xml_node node)
	{
		if (!node.has_attribute("irq"))
			return Irq_trigger { RISING };

		auto const value = node.attribute_value("irq", String<10>());

		if (value == "rising")  return Irq_trigger { RISING, OFF };
		if (value == "falling") return Irq_trigger { FALLING, OFF };
		if (value == "high")    return Irq_trigger { HIGH, OFF };
		if (value == "low")     return Irq_trigger { LOW, OFF };
		if (value == "edges")   return Irq_trigger { RISING, EDGES };

		warning("invalid irq attribute value: ", node);
		throw Invalid();
	};
};


/**
 * Pin attributes
 */
struct Pin_driver::Attr
{
	Pull        pull;
	Function    function;
	Irq_trigger irq_trigger;
	bool        out_on_demand;  /* activate output on access by 'Pin_control' client */
	Pin::Level  default_state;

	bool output() const { return function.value == Function::OUTPUT; }
	bool irq()    const { return function.value == Function::IRQ; }

	static Attr from_xml(Xml_node const &node)
	{
		auto default_state_from_xml = [] (Xml_node const &node)
		{
			if (!node.has_attribute("default"))
				return Pin::Level::HIGH_IMPEDANCE;

			return node.attribute_value("default", false)
			       ? Pin::Level::HIGH : Pin::Level::LOW;
		};

		return { Pull::from_xml(node),
		         Function::from_xml(node),
		         Irq_trigger::from_xml(node),
		         !node.has_attribute("default"),
		         default_state_from_xml(node) };
	}

	static Attr disabled()
	{
		return { { Pull::DISABLE },
		         { Function::DISABLE },
		         { Irq_trigger::RISING },
		         false,
		         Pin::Level::HIGH_IMPEDANCE };
	}

	private:

		Attr(Pull pull, Function function, Irq_trigger irq_trigger,
		     bool out_on_demand, Pin::Level default_state)
		:
			pull(pull), function(function), irq_trigger(irq_trigger),
			out_on_demand(out_on_demand), default_state(default_state)
		{ }
};

#endif /* _COMMON_TYPES_H_ */
