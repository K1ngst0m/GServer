#pragma once
#include <vector>

#include "ConfigConfig.h"
class ConfigTable : public BaseTable
{
public:
	ConfigTable() :BaseTable("Config.bin") {}
	virtual IData* ReadRow(int &id) override
	{
		auto config = new ConfigDefine(); 
		int enumTmp;

		const char* data;

		ReadValue(config->id);
		ReadValue(config->serverIP);
		id=config->id;
		return (IData*)config;
	}
};
#include "ItemConfig.h"
class ItemTable : public BaseTable
{
public:
	ItemTable() :BaseTable("Item.bin") {}
	virtual IData* ReadRow(int &id) override
	{
		auto config = new ItemDefine(); 
		int enumTmp;

		const char* data;

		ReadValue(config->id);
		ReadValue(config->type);
		ReadValue(config->name);
		ReadValue(config->quality);
		id=config->id;
		return (IData*)config;
	}
};
#include "LanguageConfig.h"
class LanguageTable : public BaseTable
{
public:
	LanguageTable() :BaseTable("Language.bin") {}
	virtual IData* ReadRow(int &id) override
	{
		auto config = new LanguageDefine(); 
		int enumTmp;

		const char* data;

		ReadValue(config->id);
		ReadValue(config->cn);
		ReadValue(config->en);
		ReadValue(config->arabic);
		ReadValue(config->tr);
		id=config->id;
		return (IData*)config;
	}
};
#include "LanguageSetConfig.h"
class LanguageSetTable : public BaseTable
{
public:
	LanguageSetTable() :BaseTable("LanguageSet.bin") {}
	virtual IData* ReadRow(int &id) override
	{
		auto config = new LanguageSetDefine(); 
		int enumTmp;

		const char* data;

		ReadValue(config->ID);
		ReadValue(config->language);
		ReadValue(config->l_languageID);
		ReadValue(config->telephone);
		ReadValue(config->enumSwitch);
		ReadValue(config->translate);
		ReadValue(config->gameID);
		ReadValue(enumTmp);
		config->test=(EunmTest)enumTmp;
		ReadValue(data);
		auto test2 = json::Deserialize(data);
		ReadValue(test2, "x", config->test2.x);
		ReadValue(test2, "y", config->test2.y);
		std::vector<std::string> vectest3;
		ReadValue(vectest3);
		for (auto value : vectest3)
		{
			auto test3 = json::Deserialize(value);
			Vec2 test3value;
			ReadValue(test3, "x", test3value.x);
			ReadValue(test3, "y", test3value.y);
			config->test3.push_back(test3value);
		}
		id=config->ID;
		return (IData*)config;
	}
};
ITable* DataService::LoadTable(const char* name)
{
	BaseTable *pTable = nullptr;

	if(strcmp("class ConfigDefine", name)==0)
	{
		pTable = new ConfigTable();
	}
	else if(strcmp("class ItemDefine", name)==0)
	{
		pTable = new ItemTable();
	}
	else if(strcmp("class LanguageDefine", name)==0)
	{
		pTable = new LanguageTable();
	}
	else if(strcmp("class LanguageSetDefine", name)==0)
	{
		pTable = new LanguageSetTable();
	}
	pTable->Load();
	return pTable;
}