#include "command_graph.h"

#include "logger.h"
#include "print_graph.h"

namespace celerity {
namespace detail {

	void command_graph::erase(abstract_command* cmd) {
		if(isa<task_command>(cmd)) {
			auto tcmd = static_cast<task_command*>(cmd);
			// TODO: If the number of commands per task gets large, this could become problematic. Maybe use an unordered_set instead?
			by_task[tcmd->get_tid()].erase(std::find(by_task[tcmd->get_tid()].begin(), by_task[tcmd->get_tid()].end(), cmd));
		}
		commands.erase(cmd->get_cid());
		execution_fronts[cmd->get_nid()].erase(cmd);
	}

	void command_graph::print_graph(logger& graph_logger) const {
		if(command_count() < 200) {
			detail::print_graph(*this, graph_logger);
		} else {
			graph_logger.warn("Command graph is very large ({} vertices). Skipping GraphViz output", command_count());
		}
	}

} // namespace detail
} // namespace celerity
