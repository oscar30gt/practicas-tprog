#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <print>

#include "shell.h"

using namespace std;

int main()
{
	Shell sh;

	for (bool done=false; !done; )
	{
		print("{}> ",sh.pwd());

		// Leer linea de entrada
		string line;
		if (!getline(cin,line))
		{
			done = true;
			continue;
		}
		if (line.empty())
			continue;

		// Separar tokens
		vector<string> cmd;
		istringstream iss(line);
		for (string tok; iss >> tok; )
			cmd.push_back(tok);

		if (cmd.empty() || cmd.front().empty())
			continue;

		try
		{
			if ((cmd[0]=="exit") || (cmd[0]=="bye"))
			{
				done = true;
			}
			else if (cmd[0]=="pwd")
			{
				println("{}",sh.pwd());
			}
			else if (cmd[0]=="ls")
			{
				println("{}",sh.ls());
			}
			else if (cmd[0]=="du")
			{
				println("{}",sh.du());
			}
			else if (cmd[0]=="mkdir")
			{
				sh.mkdir(cmd.at(1));
			}
			else if (cmd[0]=="vi")
			{
				sh.vi(cmd.at(1),stoi(cmd.at(2)));
			}
			else if (cmd[0]=="stat")
			{
				println("{}",sh.stat(cmd.at(1)));
			}
			else if (cmd[0]=="cd")
			{
				sh.cd(cmd.at(1));
			}
			else if (cmd[0]=="ln")
			{
				sh.ln(cmd.at(1),cmd.at(2));
			}
			else if (cmd[0]=="rm")
			{
				sh.rm(cmd.at(1));
			}
			else
			{
				println(cerr,"Error sintactico: comando desconocido");
			}
		}
		catch (const arbol_ficheros_error& e)
		{
			println(cerr,"{}",e.what());
		}
		catch (const out_of_range& e)
		{
			println(cerr,"Error sintactico: parametros insuficientes");
			println(cerr,"{}",e.what());
		}
	}
	println();
	println("Bye!!");

	return 0;
}
