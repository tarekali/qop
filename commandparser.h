/******************************************************************************
	QOP: Qt Output Parser for tar, zip etc with a compression/extraction progress indicator
	Copyright (C) 2011 Wangbin <wbsecg1@gmail.com>
	(aka. nukin in ccmove & novesky in http://forum.motorolafans.com)

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
******************************************************************************/

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

/*!
	You can directly write CommandParser(cmd).files(), CommandParser(cmd).archive(),
	 CommandParser(cmd).filesSize(), CommandParser(cmd).archiveUnpackSize() etc. to get the
	 correct value you need;
	 The key technology is that class CommandParser has a CommandParser pointer which points to
	 a command determined CommandParser pointer; Some CommandParser's member functions call the
	 pointer's corresponding functions.

	 You also can write code like this:
	 CommandParser cp;
	 cp.setCommand(cmd);
	 uint s=cp.archiveUnpackSize();
*/

#define COUNTER_THREAD 0
#include <qstringlist.h>

class QCounterThread;
class CommandParser
{
public:
	enum CountType {
			Size=0x0, Num=0x1, NumNoDir=0x3
	};

	CommandParser();
	CommandParser(const QString& cmd);
	//CommandParser(const QString& program, const QStringList& argv);

	virtual ~CommandParser();

	virtual void setCommand(const QString& cmd);

	virtual QStringList files();
	virtual QString archive();
	virtual CountType countType();
	virtual bool isCompressMode();

	/*!
		CommandParser(cmd).unpackSize();
	*/
	bool isSize() const;
	size_t filesCount() const;
	size_t filesSize() const;
	size_t archiveSize() const;
	size_t archiveUnpackSize() const;

	QCounterThread* counterThread() { return counter;}

protected:
	QCounterThread *counter;

	QString _cmd;
	QString _archive;
	QStringList _files;
	bool _compress_mode;
	CountType _count_type;
	CommandParser *cmd_parser;
};

class TarCommandParser : public CommandParser
{
public:
	TarCommandParser();
	TarCommandParser(const QString& cmd);
	//TarCommandParser(const QString& program, const QStringList& argv);

	virtual ~TarCommandParser();

	virtual void setCommand(const QString &cmd);
	virtual QStringList files();
	virtual QString archive();
	virtual CountType countType();
	virtual bool isCompressMode();
private:
	void init();
};

#endif // COMMANDPARSER_H
