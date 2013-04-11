#ifndef GUARD_NETLIST_H
#define GUARD_NETLIST_H

#include <vector>
#include <map>

//forward declarations
class netlist;
class gate;
class net;
class pin;

class net {
	friend class netlist;
	net() {};
	net(const net &);				//no copy
	net &operator=(const net &);	//no assignment
	std::string net_name;
protected:
	std::list<pin *> connections_;
public:
	void append_pin(pin *p);
	std::string get_net_name();
};

class pin {
	friend class gate;
	pin(const pin &);				//no copy
	pin &operator=(const pin &);	//no assignment
	pin() {};
	bool create(gate *g, size_t pin_index, const evl_pin &p, const std::map<std::string, net *> &netlist_nets);
	int value_;
	std::vector<net *> nets_;
protected:
	gate *gate_;
	size_t pin_index_;
public:
	void set_as_output();
	void set_as_input();
	void display(std::ostream &out);
	int get_pin_width();
};

class gate {
	friend class netlist;
	gate(const gate &);				//no copy
	gate &operator=(const gate &);	//no assignment
	std::string type_, name_;
	bool create_pins(const evl_pins &pins, const std::map<std::string, net *> &netlist_nets);
	bool create_pin(const evl_pin &p, size_t pin_index, const std::map<std::string, net *> &netlist_nets);
	virtual bool validate_structural_semantics() = 0;
protected:
	std::vector<pin*> pins_;
	gate(std::string type, std::string name) {
		type_ = type;
		name_ = name;}
	~gate();
public:
	std::string get_type() const;
	std::string get_name() const;
	void display(std::ostream &out);
};

class netlist {
	netlist(const netlist &);				//no copy
	netlist &operator=(const netlist &);	//no assignment
	bool create_nets(const evl_wires &wires);
	void create_net(std::string net_name);
	bool create_gates(const evl_components &comps);
	bool create_gate(const evl_component &c);
protected:
	std::list<gate *> gates_;
	std::map<std::string, net *> nets_;
public:
	netlist() {};
	~netlist();
	bool create(const evl_wires &wires, const evl_components &components);
	void save(std::string file_name);
	void display_netlist(std::ostream &out);	
};

class and_gate: public gate {
	bool state_, next_state_;
	bool validate_structural_semantics();
public:
	void compute_next_state();
	and_gate(std::string name)
		: gate("and", name), state_(false), next_state_(false) {}
};
class or_gate: public gate {
	
	bool state_, next_state_;
	bool validate_structural_semantics();

public:
	void compute_next_state();
	or_gate(std::string name)
		: gate("or", name), state_(false), next_state_(false) {}

};

class xor_gate: public gate {
	
	bool state_, next_state_;
	bool validate_structural_semantics();

public:
	void compute_next_state();
	xor_gate(std::string name)
		: gate("xor", name), state_(false), next_state_(false) {}

};

class not_gate: public gate {

	bool state_, next_state_;
	bool validate_structural_semantics();
	
public:
	void compute_next_state();
	not_gate(std::string name)
		: gate("not", name), state_(false), next_state_(false) {}
};

class buffer: public gate {

	bool state_, next_state_;
	bool validate_structural_semantics();
	
public:
	void compute_next_state();
	buffer(std::string name)
		: gate("buf", name), state_(false), next_state_(false) {}
};

class flip_flop: public gate {

	bool state_, next_state_;
	bool validate_structural_semantics();
	
public:
	void compute_next_state();
	flip_flop(std::string name)
		: gate("dff", name), state_(false), next_state_(false) {}
};

class one: public gate {

	bool state_, next_state_;
	bool validate_structural_semantics();
	
public:
	void compute_next_state();
	one(std::string name)
		: gate("one", name), state_(false), next_state_(false) {}
};

class zero: public gate {

	bool state_, next_state_;
	bool validate_structural_semantics();
	
public:
	void compute_next_state();
	zero(std::string name)
		: gate("zero", name), state_(false), next_state_(false) {}
};

class input: public gate {

	bool state_, next_state_;
	bool validate_structural_semantics();
	
public:
	void compute_next_state();
	input(std::string name)
		: gate("input", name), state_(false), next_state_(false) {}
};

class output: public gate {

	bool state_, next_state_;
	bool validate_structural_semantics();
	
public:
	void compute_next_state();
	output(std::string name)
		: gate("output", name), state_(false), next_state_(false) {}
};



#endif