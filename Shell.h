#ifndef SHELL_H
#define SHELL_H
typedef char * string;
class Shell {
	public:
		void begin();
		char scan();
		void update(char c);
		int request;
		int response;
		void end();
		void execute(string cmd);
};

#endif
