//
// ConfigurationMapperTest.cpp
//
// $Id: //poco/1.3/Util/testsuite/src/ConfigurationMapperTest.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "ConfigurationMapperTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Util/ConfigurationMapper.h"
#include "Poco/Util/MapConfiguration.h"
#include "Poco/AutoPtr.h"
#include "Poco/Exception.h"
#include <algorithm>


using Poco::Util::AbstractConfiguration;
using Poco::Util::ConfigurationMapper;
using Poco::Util::MapConfiguration;
using Poco::AutoPtr;


ConfigurationMapperTest::ConfigurationMapperTest(const std::string& name): CppUnit::TestCase(name)
{
}


ConfigurationMapperTest::~ConfigurationMapperTest()
{
}


void ConfigurationMapperTest::testMapper1()
{
	AutoPtr<AbstractConfiguration> pConf = createConfiguration();
	AutoPtr<AbstractConfiguration> pMapper = new ConfigurationMapper("", "", pConf);
	assert (pMapper->hasProperty("config.value1"));
	assert (pMapper->hasProperty("config.value2"));

	AbstractConfiguration::Keys keys;
	pMapper->keys(keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "config") != keys.end());

	pMapper->keys("config", keys);
	assert (keys.size() == 3);
	assert (std::find(keys.begin(), keys.end(), "value1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "value2") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub") != keys.end());
	
	assert (pMapper->getString("config.value1") == "v1");
	assert (pMapper->getString("config.sub.value2") == "v4");
	
	pMapper->setString("config.value3", "v5");
	assert (pMapper->getString("config.value3") == "v5");
	assert (pConf->getString("config.value3") == "v5");
}


void ConfigurationMapperTest::testMapper2()
{
	AutoPtr<AbstractConfiguration> pConf = createConfiguration();
	AutoPtr<AbstractConfiguration> pMapper = new ConfigurationMapper("config", "root.conf", pConf);

	assert (pMapper->hasProperty("root.conf.value1"));
	assert (pMapper->hasProperty("root.conf.value2"));

	AbstractConfiguration::Keys keys;
	pMapper->keys(keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "root") != keys.end());

	pMapper->keys("root", keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "conf") != keys.end());

	pMapper->keys("root.conf", keys);
	assert (keys.size() == 3);
	assert (std::find(keys.begin(), keys.end(), "value1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "value2") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub") != keys.end());

	assert (pMapper->getString("root.conf.value1") == "v1");
	assert (pMapper->getString("root.conf.sub.value2") == "v4");
	
	pMapper->setString("root.conf.value3", "v5");
	assert (pMapper->getString("root.conf.value3") == "v5");
	assert (pConf->getString("config.value3") == "v5");
}


void ConfigurationMapperTest::testMapper3()
{
	AutoPtr<AbstractConfiguration> pConf = createConfiguration();
	AutoPtr<AbstractConfiguration> pMapper = new ConfigurationMapper("", "root", pConf);

	assert (pMapper->hasProperty("root.config.value1"));
	assert (pMapper->hasProperty("root.config.value2"));

	AbstractConfiguration::Keys keys;
	pMapper->keys(keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "root") != keys.end());

	pMapper->keys("root", keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "config") != keys.end());

	pMapper->keys("root.config", keys);
	assert (keys.size() == 3);
	assert (std::find(keys.begin(), keys.end(), "value1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "value2") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub") != keys.end());
	
	assert (pMapper->getString("root.config.value1") == "v1");
	assert (pMapper->getString("root.config.sub.value2") == "v4");
	
	pMapper->setString("root.config.value3", "v5");
	assert (pMapper->getString("root.config.value3") == "v5");
	assert (pConf->getString("config.value3") == "v5");
}


void ConfigurationMapperTest::testMapper4()
{
	AutoPtr<AbstractConfiguration> pConf = createConfiguration();
	AutoPtr<AbstractConfiguration> pMapper = new ConfigurationMapper("config", "", pConf);

	assert (pMapper->hasProperty("value1"));
	assert (pMapper->hasProperty("value2"));

	AbstractConfiguration::Keys keys;
	pMapper->keys(keys);
	assert (keys.size() == 3);
	assert (std::find(keys.begin(), keys.end(), "value1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "value2") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub") != keys.end());
	
	assert (pMapper->getString("value1") == "v1");
	assert (pMapper->getString("sub.value2") == "v4");
	
	pMapper->setString("value3", "v5");
	assert (pMapper->getString("value3") == "v5");
	assert (pConf->getString("config.value3") == "v5");
}


AbstractConfiguration* ConfigurationMapperTest::createConfiguration() const
{
	AbstractConfiguration* pConfig = new MapConfiguration;
	
	pConfig->setString("config.value1", "v1");
	pConfig->setString("config.value2", "v2");
	pConfig->setString("config.sub.value1", "v3");
	pConfig->setString("config.sub.value2", "v4");
	
	return pConfig;
}


void ConfigurationMapperTest::setUp()
{
}


void ConfigurationMapperTest::tearDown()
{
}


CppUnit::Test* ConfigurationMapperTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ConfigurationMapperTest");

	CppUnit_addTest(pSuite, ConfigurationMapperTest, testMapper1);
	CppUnit_addTest(pSuite, ConfigurationMapperTest, testMapper2);
	CppUnit_addTest(pSuite, ConfigurationMapperTest, testMapper3);
	CppUnit_addTest(pSuite, ConfigurationMapperTest, testMapper4);

	return pSuite;
}
