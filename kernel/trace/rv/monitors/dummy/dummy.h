/*
 * Automatically generated C representation of dummy automaton
 * For further information about this format, see kernel documentation:
 *   Documentation/trace/rv/deterministic_automata.rst
 */

enum states_dummy {
	closed_dummy = 0,
	open_dummy,
	state_max_dummy
};

#define INVALID_STATE state_max_dummy

enum events_dummy {
	dummy_close_dummy = 0,
	dummy_open_dummy,
	dummy_write_dummy,
	event_max_dummy
};

struct automaton_dummy {
	char *state_names[state_max_dummy];
	char *event_names[event_max_dummy];
	unsigned char function[state_max_dummy][event_max_dummy];
	unsigned char initial_state;
	bool final_states[state_max_dummy];
};

static const struct automaton_dummy automaton_dummy = {
	.state_names = {
		"closed",
		"open"
	},
	.event_names = {
		"dummy_close",
		"dummy_open",
		"dummy_write"
	},
	.function = {
		{       INVALID_STATE,          open_dummy,       INVALID_STATE },
		{        closed_dummy,       INVALID_STATE,          open_dummy },
	},
	.initial_state = closed_dummy,
	.final_states = { 1, 0 },
};
