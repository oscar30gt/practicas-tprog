#include <cassert>
#include <iostream>
#include <sstream>

#include "shell.h"

using namespace std;

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

void printTestHeader(const string &testName)
{
	cout << "\n"
		 << GREEN << "===== " << testName << " =====" << RESET << "\n";
}

void printTestResult(bool passed)
{
	cout << (passed ? GREEN : RED) << (passed ? "✓ PASSED" : "✗ FAILED") << RESET << "\n";
}

// ======================= TEST GROUP 1: BASIC COMMANDS =======================

void testPwdInitial()
{
	printTestHeader("Test PWD Initial");
	Shell sh;
	assert(sh.pwd() == "/");
	printTestResult(true);
}

void testLsInitial()
{
	printTestHeader("Test LS Initial (should be empty)");
	Shell sh;
	string ls_output = sh.ls();
	assert(ls_output.find("WARNING") == string::npos); // Should not have items
	printTestResult(true);
}

void testDuInitial()
{
	printTestHeader("Test DU Initial (should show header only)");
	Shell sh;
	string du_output = sh.du();
	assert(du_output.find("NAME") != string::npos);
	assert(du_output.find("SIZE") != string::npos);
	printTestResult(true);
}

// ======================= TEST GROUP 2: FILE CREATION WITH VI =======================

void testViCreateSimpleFile()
{
	printTestHeader("Test VI Create Simple File");
	Shell sh;
	sh.vi("file1.txt", 100);
	string ls_output = sh.ls();
	assert(ls_output.find("file1.txt") != string::npos);
	printTestResult(true);
}

void testViCreateMultipleFiles()
{
	printTestHeader("Test VI Create Multiple Files");
	Shell sh;
	sh.vi("file1.txt", 50);
	sh.vi("file2.txt", 100);
	sh.vi("file3.txt", 150);
	string ls_output = sh.ls();
	assert(ls_output.find("file1.txt") != string::npos);
	assert(ls_output.find("file2.txt") != string::npos);
	assert(ls_output.find("file3.txt") != string::npos);
	printTestResult(true);
}

void testViModifyExistingFile()
{
	printTestHeader("Test VI Modify Existing File");
	Shell sh;
	sh.vi("file.txt", 100);
	string stat1 = sh.stat("file.txt");
	assert(stat1.find("100") != string::npos);

	sh.vi("file.txt", 200);
	string stat2 = sh.stat("file.txt");
	assert(stat2.find("200") != string::npos);
	printTestResult(true);
}

void testViVariousSizes()
{
	printTestHeader("Test VI Various File Sizes");
	Shell sh;
	sh.vi("small", 1);
	sh.vi("medium", 1024);
	sh.vi("large", 10000);

	assert(sh.stat("small").find("1 Bytes") != string::npos);
	assert(sh.stat("medium").find("1024 Bytes") != string::npos);
	assert(sh.stat("large").find("10000 Bytes") != string::npos);
	printTestResult(true);
}

void testViZeroSize()
{
	printTestHeader("Test VI Zero Size File");
	Shell sh;
	sh.vi("empty", 0);
	assert(sh.stat("empty").find("0 Bytes") != string::npos);
	printTestResult(true);
}

void testViInvalidNameWithSlash()
{
	printTestHeader("Test VI Invalid Name With Slash");
	Shell sh;
	try
	{
		sh.vi("file/name", 100);
		assert(false && "Should have thrown bad_identifier_error");
	}
	catch (const bad_identifier_error &e)
	{
		printTestResult(true);
	}
}

void testViInvalidNameDot()
{
	printTestHeader("Test VI Invalid Name '.'");
	Shell sh;
	try
	{
		sh.vi(".", 100);
		assert(false);
	}
	catch (const bad_identifier_error &e)
	{
		printTestResult(true);
	}
}

void testViInvalidNameDotDot()
{
	printTestHeader("Test VI Invalid Name '..'");
	Shell sh;
	try
	{
		sh.vi("..", 100);
		assert(false);
	}
	catch (const bad_identifier_error &e)
	{
		printTestResult(true);
	}
}

// ======================= TEST GROUP 3: DIRECTORY CREATION (MKDIR) =======================

void testMkdirBasic()
{
	printTestHeader("Test MKDIR Basic");
	Shell sh;
	sh.mkdir("dir1");
	string ls_output = sh.ls();
	assert(ls_output.find("dir1") != string::npos);
	printTestResult(true);
}

void testMkdirMultipleDirs()
{
	printTestHeader("Test MKDIR Multiple Directories");
	Shell sh;
	sh.mkdir("dir1");
	sh.mkdir("dir2");
	sh.mkdir("dir3");
	string ls_output = sh.ls();
	assert(ls_output.find("dir1") != string::npos);
	assert(ls_output.find("dir2") != string::npos);
	assert(ls_output.find("dir3") != string::npos);
	printTestResult(true);
}

void testMkdirAlreadyExists()
{
	printTestHeader("Test MKDIR Already Exists");
	Shell sh;
	sh.mkdir("dir1");
	try
	{
		sh.mkdir("dir1");
		assert(false && "Should have thrown already_exists_error");
	}
	catch (const already_exists_error &e)
	{
		printTestResult(true);
	}
}

void testMkdirInvalidNameWithSlash()
{
	printTestHeader("Test MKDIR Invalid Name With Slash");
	Shell sh;
	try
	{
		sh.mkdir("dir/subdir");
		assert(false);
	}
	catch (const bad_identifier_error &e)
	{
		printTestResult(true);
	}
}

void testMkdirInvalidNameDot()
{
	printTestHeader("Test MKDIR Invalid Name '.'");
	Shell sh;
	try
	{
		sh.mkdir(".");
		assert(false);
	}
	catch (const bad_identifier_error &e)
	{
		printTestResult(true);
	}
}

void testMkdirInvalidNameDotDot()
{
	printTestHeader("Test MKDIR Invalid Name '..'");
	Shell sh;
	try
	{
		sh.mkdir("..");
		assert(false);
	}
	catch (const bad_identifier_error &e)
	{
		printTestResult(true);
	}
}

// ======================= TEST GROUP 4: NAVIGATION (CD) =======================

void testCdToCreatedDir()
{
	printTestHeader("Test CD To Created Directory");
	Shell sh;
	sh.mkdir("subdir");
	sh.cd("subdir");
	assert(sh.pwd() == "/subdir");
	printTestResult(true);
}

void testCdMultipleLevels()
{
	printTestHeader("Test CD Multiple Levels");
	Shell sh;
	sh.mkdir("a");
	sh.cd("a");
	sh.mkdir("b");
	sh.cd("b");
	sh.mkdir("c");
	sh.cd("c");
	assert(sh.pwd() == "/a/b/c");
	printTestResult(true);
}

void testCdDotDot()
{
	printTestHeader("Test CD .. (go up)");
	Shell sh;
	sh.mkdir("a");
	sh.cd("a");
	sh.mkdir("b");
	sh.cd("b");
	assert(sh.pwd() == "/a/b");
	sh.cd("..");
	assert(sh.pwd() == "/a");
	sh.cd("..");
	assert(sh.pwd() == "/");
	printTestResult(true);
}

void testCdAbsolutePath()
{
	printTestHeader("Test CD Absolute Path");
	Shell sh;
	sh.mkdir("a");
	sh.mkdir("b");
	sh.cd("a");
	assert(sh.pwd() == "/a");
	sh.cd("/b");
	assert(sh.pwd() == "/b");
	sh.cd("/");
	assert(sh.pwd() == "/");
	printTestResult(true);
}

void testCdRelativePath()
{
	printTestHeader("Test CD Relative Path (multiple levels)");
	Shell sh;
	sh.mkdir("a");
	sh.mkdir("b");
	sh.cd("a");
	sh.mkdir("c");
	sh.cd("../b");
	assert(sh.pwd() == "/b");
	printTestResult(true);
}

void testCdRoot()
{
	printTestHeader("Test CD To Root");
	Shell sh;
	sh.mkdir("dir");
	sh.cd("dir");
	sh.cd("/");
	assert(sh.pwd() == "/");
	printTestResult(true);
}

void testCdNonexistentPath()
{
	printTestHeader("Test CD Non-existent Path");
	Shell sh;
	try
	{
		sh.cd("nonexistent");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testCdToFile()
{
	printTestHeader("Test CD To File (should fail)");
	Shell sh;
	sh.vi("file.txt", 100);
	try
	{
		sh.cd("file.txt");
		assert(false);
	}
	catch (const invalid_type_error &e)
	{
		printTestResult(true);
	}
}

void testCdAboveRoot()
{
	printTestHeader("Test CD Above Root");
	Shell sh;
	try
	{
		sh.cd("/..");
		assert(false);
	}
	catch (const illegal_action_error &e)
	{
		printTestResult(true);
	}
}

void testCdDotDotAtRoot()
{
	printTestHeader("Test CD .. At Root (should fail)");
	Shell sh;
	try
	{
		sh.cd("..");
		assert(false);
	}
	catch (const illegal_action_error &e)
	{
		printTestResult(true);
	}
}

void testCdComplexPath()
{
	printTestHeader("Test CD Complex Path Navigation");
	Shell sh;
	sh.mkdir("a");
	sh.mkdir("b");
	sh.cd("a");
	sh.mkdir("c");
	sh.cd("c");
	sh.mkdir("d");
	sh.cd("../../b");
	assert(sh.pwd() == "/b");
	sh.cd("../a/c/d");
	assert(sh.pwd() == "/a/c/d");
	printTestResult(true);
}

// ======================= TEST GROUP 5: STAT COMMAND =======================

void testStatFile()
{
	printTestHeader("Test STAT File");
	Shell sh;
	sh.vi("file.txt", 512);
	string stat_output = sh.stat("file.txt");
	assert(stat_output.find("512 Bytes") != string::npos);
	printTestResult(true);
}

void testStatDirectory()
{
	printTestHeader("Test STAT Directory");
	Shell sh;
	sh.mkdir("dir");
	string stat_output = sh.stat("dir");
	assert(stat_output.find("0 Bytes") != string::npos); // Empty directory
	printTestResult(true);
}

void testStatDirectoryWithFiles()
{
	printTestHeader("Test STAT Directory With Files");
	Shell sh;
	sh.mkdir("dir");
	sh.vi("file1", 100);
	sh.vi("file2", 200);
	string stat_dir = sh.stat("dir");
	assert(stat_dir.find("0 Bytes") != string::npos); // dir has no files

	sh.cd("dir");
	sh.vi("inner.txt", 150);
	sh.cd("..");
	stat_dir = sh.stat("dir");
	assert(stat_dir.find("150 Bytes") != string::npos);
	printTestResult(true);
}

void testStatAbsolutePath()
{
	printTestHeader("Test STAT Absolute Path");
	Shell sh;
	sh.mkdir("a");
	sh.cd("a");
	sh.vi("file.txt", 300);
	sh.cd("/");
	string stat_output = sh.stat("/a/file.txt");
	assert(stat_output.find("300 Bytes") != string::npos);
	printTestResult(true);
}

void testStatRelativePath()
{
	printTestHeader("Test STAT Relative Path");
	Shell sh;
	sh.mkdir("a");
	sh.mkdir("b");
	sh.cd("a");
	sh.vi("file.txt", 250);
	sh.cd("/b");
	string stat_output = sh.stat("../a/file.txt");
	assert(stat_output.find("250 Bytes") != string::npos);
	printTestResult(true);
}

void testStatNonexistent()
{
	printTestHeader("Test STAT Non-existent Path");
	Shell sh;
	try
	{
		sh.stat("nonexistent");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testStatDeeplyNestedDirectory()
{
	printTestHeader("Test STAT Deeply Nested Directory");
	Shell sh;
	sh.mkdir("a");
	sh.cd("a");
	sh.mkdir("b");
	sh.cd("b");
	sh.mkdir("c");
	sh.cd("c");
	sh.vi("file", 999);
	sh.cd("/");
	string stat_output = sh.stat("/a/b/c/file");
	assert(stat_output.find("999 Bytes") != string::npos);
	printTestResult(true);
}

// ======================= TEST GROUP 6: LINKS (LN) =======================

void testLnCreateSimpleLink()
{
	printTestHeader("Test LN Create Simple Link To File");
	Shell sh;
	sh.vi("original", 100);
	sh.ln("original", "link");
	string ls_output = sh.ls();
	assert(ls_output.find("link") != string::npos);
	assert(sh.stat("link").find("100 Bytes") != string::npos);
	printTestResult(true);
}

void testLnLinkToDirectory()
{
	printTestHeader("Test LN Create Link To Directory");
	Shell sh;
	sh.mkdir("original_dir");
	sh.ln("original_dir", "linked_dir");
	string ls_output = sh.ls();
	assert(ls_output.find("linked_dir") != string::npos);
	printTestResult(true);
}

void testLnAccessThroughLink()
{
	printTestHeader("Test LN Access Directory Through Link");
	Shell sh;
	sh.mkdir("original");
	sh.cd("original");
	sh.vi("file.txt", 200);
	sh.cd("/");
	sh.ln("original", "link");
	string stat_output = sh.stat("link/file.txt");
	assert(stat_output.find("200 Bytes") != string::npos);
	printTestResult(true);
}

void testLnCdThroughLink()
{
	printTestHeader("Test LN CD Through Link");
	Shell sh;
	sh.mkdir("original");
	sh.ln("original", "link");
	sh.cd("link");
	assert(sh.pwd() == "/link");
	sh.vi("file.txt", 100);
	sh.cd("/");
	string stat_output = sh.stat("original/file.txt");
	assert(stat_output.find("100 Bytes") != string::npos);
	printTestResult(true);
}

void testLnMultipleLinksToSame()
{
	printTestHeader("Test LN Multiple Links To Same Node");
	Shell sh;
	sh.vi("original", 500);
	sh.ln("original", "link1");
	sh.ln("original", "link2");
	sh.ln("original", "link3");
	assert(sh.stat("link1").find("500 Bytes") != string::npos);
	assert(sh.stat("link2").find("500 Bytes") != string::npos);
	assert(sh.stat("link3").find("500 Bytes") != string::npos);
	printTestResult(true);
}

void testLnAbsolutePath()
{
	printTestHeader("Test LN Absolute Path");
	Shell sh;
	sh.mkdir("a");
	sh.mkdir("b");
	sh.cd("a");
	sh.vi("file", 300);
	sh.cd("..");
	sh.cd("b");
	sh.ln("/a/file", "link");
	assert(sh.stat("link").find("300 Bytes") != string::npos);
	printTestResult(true);
}

void testLnRelativePath()
{
	printTestHeader("Test LN Relative Path");
	Shell sh;
	sh.mkdir("a");
	sh.mkdir("b");
	sh.cd("a");
	sh.vi("file", 300);
	sh.cd("/b");
	sh.ln("../a/file", "link");
	assert(sh.stat("link").find("300 Bytes") != string::npos);
	printTestResult(true);
}

void testLnNameAlreadyExists()
{
	printTestHeader("Test LN Name Already Exists");
	Shell sh;
	sh.vi("file1", 100);
	sh.vi("file2", 200);
	try
	{
		sh.ln("file1", "file2");
		assert(false);
	}
	catch (const already_exists_error &e)
	{
		printTestResult(true);
	}
}

void testLnInvalidName()
{
	printTestHeader("Test LN Invalid Name With Slash");
	Shell sh;
	sh.vi("file", 100);
	try
	{
		sh.ln("file", "link/name");
		assert(false);
	}
	catch (const bad_identifier_error &e)
	{
		printTestResult(true);
	}
}

void testLnNonexistentTarget()
{
	printTestHeader("Test LN Non-existent Target");
	Shell sh;
	try
	{
		sh.ln("nonexistent", "link");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testLnCircularReference()
{
	printTestHeader("Test LN Circular Reference Detection");
	Shell sh;
	sh.mkdir("dir1");
	sh.cd("dir1");
	sh.mkdir("dir2");
	try
	{
		sh.cd("dir2");
		// Now we're in /dir1/dir2. Try to link /dir1 (which contains current dir) here
		sh.ln("/dir1", "link_to_parent");
		assert(false && "Should have thrown illegal_action_error for circular reference");
	}
	catch (const illegal_action_error &e)
	{
		printTestResult(true);
	}
}

void testLnDeepCircularReference()
{
	printTestHeader("Test LN Deep Circular Reference Detection");
	Shell sh;
	sh.mkdir("a");
	sh.cd("a");
	sh.mkdir("b");
	sh.cd("b");
	sh.mkdir("c");
	sh.cd("c");
	// Now we're in /a/b/c. Try to link /a (which is an ancestor and contains us)
	try
	{
		sh.ln("/a", "circular_link");
		assert(false);
	}
	catch (const illegal_action_error &e)
	{
		printTestResult(true);
	}
}

void testLnCreateLinkToDotDot()
{
	printTestHeader("Test LN With Invalid Name '..'");
	Shell sh;
	sh.mkdir("dir");
	try
	{
		sh.ln("dir", "..");
		assert(false);
	}
	catch (const bad_identifier_error &e)
	{
		printTestResult(true);
	}
}

// ======================= TEST GROUP 7: REMOVAL (RM) =======================

void testRmFile()
{
	printTestHeader("Test RM File");
	Shell sh;
	sh.vi("file.txt", 100);
	assert(sh.ls().find("file.txt") != string::npos);
	sh.rm("file.txt");
	try
	{
		sh.stat("file.txt");
		assert(false && "File should have been deleted");
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testRmDirectory()
{
	printTestHeader("Test RM Directory");
	Shell sh;
	sh.mkdir("dir");
	assert(sh.ls().find("dir") != string::npos);
	sh.rm("dir");
	try
	{
		sh.stat("dir");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testRmDirectoryWithContents()
{
	printTestHeader("Test RM Directory With Contents");
	Shell sh;
	sh.mkdir("dir");
	sh.cd("dir");
	sh.vi("file.txt", 100);
	sh.cd("/");
	sh.rm("dir");
	try
	{
		sh.stat("dir");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testRmLink()
{
	printTestHeader("Test RM Link (should remove only link)");
	Shell sh;
	sh.vi("file", 100);
	sh.ln("file", "link");
	sh.rm("link");
	try
	{
		sh.stat("link");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		// Link removed
	}
	// Original file should still exist
	assert(sh.stat("file").find("100 Bytes") != string::npos);
	printTestResult(true);
}

void testRmNonexistent()
{
	printTestHeader("Test RM Non-existent");
	Shell sh;
	try
	{
		sh.rm("nonexistent");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testRmRoot()
{
	printTestHeader("Test RM Root Directory");
	Shell sh;
	try
	{
		sh.rm("/");
		assert(false && "Should not be able to remove root");
	}
	catch (const illegal_action_error &e)
	{
		printTestResult(true);
	}
}

void testRmAbsolutePath()
{
	printTestHeader("Test RM Absolute Path");
	Shell sh;
	sh.mkdir("a");
	sh.vi("file", 100);
	sh.cd("a");
	sh.rm("/file");
	sh.cd("/");
	try
	{
		sh.stat("file");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testRmRelativePath()
{
	printTestHeader("Test RM Relative Path");
	Shell sh;
	sh.mkdir("a");
	sh.mkdir("b");
	sh.cd("a");
	sh.vi("file", 200);
	sh.cd("/b");
	sh.rm("../a/file");
	sh.cd("/");
	try
	{
		sh.stat("a/file");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testRmFromDirectory()
{
	printTestHeader("Test RM From Within CWD");
	Shell sh;
	sh.mkdir("dir");
	sh.cd("dir");
	sh.vi("file", 100);
	sh.cd("/");
	sh.cd("dir");
	sh.rm("file");
	try
	{
		sh.stat("file");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		printTestResult(true);
	}
}

void testRmCdThroughLink()
{
	printTestHeader("Test RM Node Accessed Through Link (keeps alive)");
	Shell sh;
	sh.mkdir("dir");
	sh.ln("dir", "link");
	sh.cd("link");
	sh.vi("file", 100);
	sh.cd("/");
	sh.rm("link");
	// Directory should still be accessible through original path
	// because we accessed it through link (nlinks remains > 1)
	assert(sh.stat("dir/file").find("100 Bytes") != string::npos);
	printTestResult(true);
}

void testRmMultipleLinksLastRemains()
{
	printTestHeader("Test RM When Multiple Links Exist");
	Shell sh;
	sh.vi("file", 100);
	sh.ln("file", "link1");
	sh.ln("file", "link2");
	sh.rm("file");
	// Links should still work
	assert(sh.stat("link1").find("100 Bytes") != string::npos);
	assert(sh.stat("link2").find("100 Bytes") != string::npos);
	printTestResult(true);
}

// ======================= TEST GROUP 8: DU COMMAND =======================

void testDuEmpty()
{
	printTestHeader("Test DU Empty Directory");
	Shell sh;
	string du_output = sh.du();
	assert(du_output.find("NAME") != string::npos);
	assert(du_output.find("SIZE") != string::npos);
	printTestResult(true);
}

void testDuWithFiles()
{
	printTestHeader("Test DU With Files");
	Shell sh;
	sh.vi("file1", 100);
	sh.vi("file2", 200);
	string du_output = sh.du();
	assert(du_output.find("file1") != string::npos);
	assert(du_output.find("file2") != string::npos);
	assert(du_output.find("100") != string::npos);
	assert(du_output.find("200") != string::npos);
	printTestResult(true);
}

void testDuWithDirectories()
{
	printTestHeader("Test DU With Directories");
	Shell sh;
	sh.mkdir("dir1");
	sh.mkdir("dir2");
	sh.cd("dir1");
	sh.vi("file", 150);
	sh.cd("/");
	string du_output = sh.du();
	assert(du_output.find("dir1") != string::npos);
	assert(du_output.find("dir2") != string::npos);
	assert(du_output.find("150") != string::npos); // dir1 contains 150
	printTestResult(true);
}

void testDuMixed()
{
	printTestHeader("Test DU Mixed Files and Directories");
	Shell sh;
	sh.vi("file1", 100);
	sh.mkdir("dir");
	sh.cd("dir");
	sh.vi("file2", 250);
	sh.vi("file3", 250);
	sh.cd("/");
	string du_output = sh.du();
	assert(du_output.find("file1") != string::npos);
	assert(du_output.find("dir") != string::npos);
	assert(du_output.find("500") != string::npos); // dir has 250 + 250
	printTestResult(true);
}

// ======================= TEST GROUP 9: LS COMMAND =======================

void testLsAfterViCreation()
{
	printTestHeader("Test LS After VI Creation");
	Shell sh;
	sh.vi("file1", 100);
	sh.vi("file2", 200);
	string ls_output = sh.ls();
	assert(ls_output.find("file1") != string::npos);
	assert(ls_output.find("file2") != string::npos);
	printTestResult(true);
}

void testLsAfterMkdir()
{
	printTestHeader("Test LS After MKDIR");
	Shell sh;
	sh.mkdir("dir1");
	sh.mkdir("dir2");
	string ls_output = sh.ls();
	assert(ls_output.find("dir1") != string::npos);
	assert(ls_output.find("dir2") != string::npos);
	printTestResult(true);
}

void testLsWithLinks()
{
	printTestHeader("Test LS With Links");
	Shell sh;
	sh.vi("file", 100);
	sh.ln("file", "link");
	string ls_output = sh.ls();
	assert(ls_output.find("file") != string::npos);
	assert(ls_output.find("link") != string::npos);
	printTestResult(true);
}

void testLsInSubdirectory()
{
	printTestHeader("Test LS In Subdirectory");
	Shell sh;
	sh.mkdir("dir");
	sh.cd("dir");
	sh.vi("file1", 100);
	sh.vi("file2", 200);
	string ls_output = sh.ls();
	assert(ls_output.find("file1") != string::npos);
	assert(ls_output.find("file2") != string::npos);
	printTestResult(true);
}

// ======================= TEST GROUP 10: COMPLEX SCENARIOS =======================

void testComplexScenarioDeepStructure()
{
	printTestHeader("Test Complex Scenario: Deep Directory Structure");
	Shell sh;
	sh.mkdir("a");
	sh.cd("a");
	sh.mkdir("b");
	sh.cd("b");
	sh.mkdir("c");
	sh.cd("c");
	sh.vi("file.txt", 1000);
	assert(sh.pwd() == "/a/b/c");

	sh.cd("/");
	assert(sh.stat("/a/b/c/file.txt").find("1000 Bytes") != string::npos);

	sh.cd("a");
	sh.cd("b");
	sh.vi("file2.txt", 500);
	sh.cd("/");

	string du_a = sh.stat("a");
	assert(du_a.find("1500") != string::npos); // 1000 + 500
	printTestResult(true);
}

void testComplexScenarioMultipleLinks()
{
	printTestHeader("Test Complex Scenario: Multiple Links Chain");
	Shell sh;
	sh.vi("original", 999);
	sh.ln("original", "link1");
	sh.ln("link1", "link2");
	sh.ln("link2", "link3");

	assert(sh.stat("original").find("999 Bytes") != string::npos);
	assert(sh.stat("link1").find("999 Bytes") != string::npos);
	assert(sh.stat("link2").find("999 Bytes") != string::npos);
	assert(sh.stat("link3").find("999 Bytes") != string::npos);
	printTestResult(true);
}

void testComplexScenarioLinkToDirectoryNavigation()
{
	printTestHeader("Test Complex Scenario: Link To Directory Navigation");
	Shell sh;
	sh.mkdir("original_dir");
	sh.cd("original_dir");
	sh.mkdir("sub1");
	sh.mkdir("sub2");
	sh.cd("sub1");
	sh.vi("file", 100);
	sh.cd("/");

	sh.ln("original_dir", "linked_dir");
	sh.cd("linked_dir/sub1");
	assert(sh.pwd() == "/linked_dir/sub1");
	assert(sh.stat("file").find("100 Bytes") != string::npos);

	sh.cd("/");
	sh.cd("original_dir/sub2");
	assert(sh.pwd() == "/original_dir/sub2");
	printTestResult(true);
}

void testComplexScenarioMixedOperations()
{
	printTestHeader("Test Complex Scenario: Mixed Operations");
	Shell sh;

	// Create structure
	sh.mkdir("projects");
	sh.cd("projects");
	sh.mkdir("project1");
	sh.mkdir("project2");
	sh.cd("project1");
	sh.vi("main.cpp", 2000);
	sh.vi("header.h", 500);
	sh.mkdir("build");
	sh.cd("build");
	sh.vi("output.bin", 10000);
	sh.cd("/");

	// Create links
	sh.ln("projects/project1", "current_project");
	sh.ln("projects/project1/main.cpp", "main");

	// Navigate and check
	sh.cd("current_project/build");
	assert(sh.pwd() == "/current_project/build");
	assert(sh.stat("output.bin").find("10000 Bytes") != string::npos);

	// Remove a file through one path
	sh.cd("/");
	sh.rm("main");

	// File should still exist through original path
	sh.stat("projects/project1/main.cpp");

	printTestResult(true);
}

void testComplexScenarioRmWithLinks()
{
	printTestHeader("Test Complex Scenario: RM With Multiple Links");
	Shell sh;
	sh.mkdir("data");
	sh.ln("data", "link1");
	sh.ln("link1", "link2");
	sh.cd("link2");
	sh.vi("file", 500);
	sh.cd("/");

	// All paths should access the same file
	assert(sh.stat("data/file").find("500 Bytes") != string::npos);
	assert(sh.stat("link1/file").find("500 Bytes") != string::npos);
	assert(sh.stat("link2/file").find("500 Bytes") != string::npos);

	// Remove link2
	sh.rm("link2");

	// File still accessible through other paths
	assert(sh.stat("data/file").find("500 Bytes") != string::npos);
	assert(sh.stat("link1/file").find("500 Bytes") != string::npos);

	// But not through link2
	try
	{
		sh.stat("link2/file");
		assert(false);
	}
	catch (const path_not_found_error &e)
	{
		// Expected
	}

	printTestResult(true);
}

void testComplexScenarioPathResolution()
{
	printTestHeader("Test Complex Scenario: Complex Path Resolution");
	Shell sh;
	sh.mkdir("a");
	sh.mkdir("b");
	sh.cd("a");
	sh.mkdir("c");
	sh.cd("c");
	sh.mkdir("d");
	sh.cd("/b");

	// Navigate using ../ and various paths
	sh.cd("../a/c");
	assert(sh.pwd() == "/a/c");

	sh.cd("d");
	assert(sh.pwd() == "/a/c/d");

	sh.cd("../../../a");
	assert(sh.pwd() == "/a");

	sh.cd("/");
	assert(sh.pwd() == "/");

	printTestResult(true);
}

void testComplexScenarioPwdAfterOperations()
{
	printTestHeader("Test Complex Scenario: PWD After Various Operations");
	Shell sh;
	sh.mkdir("x");
	sh.mkdir("y");
	sh.cd("x");
	assert(sh.pwd() == "/x");

	sh.mkdir("z");
	assert(sh.pwd() == "/x");

	sh.vi("file", 100);
	assert(sh.pwd() == "/x");

	sh.cd("/y");
	assert(sh.pwd() == "/y");

	sh.ln("/x/file", "link");
	assert(sh.pwd() == "/y");

	sh.rm("link");
	assert(sh.pwd() == "/y");

	printTestResult(true);
}

// ======================= STRESS TESTS =======================

void testStressCreateMany()
{
	printTestHeader("Test Stress: Create Many Files");
	Shell sh;
	for (int i = 0; i < 100; i++)
	{
		sh.vi("file" + to_string(i), i * 10);
	}
	string ls_output = sh.ls();
	assert(ls_output.find("file0") != string::npos);
	assert(ls_output.find("file99") != string::npos);
	printTestResult(true);
}

void testStressCreateDeepNesting()
{
	printTestHeader("Test Stress: Deep Directory Nesting");
	Shell sh;
	for (int i = 0; i < 50; i++)
	{
		sh.mkdir("d" + to_string(i));
		sh.cd("d" + to_string(i));
	}
	assert(sh.pwd().find("d49") != string::npos);

	// Navigate back
	for (int i = 0; i < 50; i++)
	{
		sh.cd("..");
	}
	assert(sh.pwd() == "/");
	printTestResult(true);
}

void testStressMultipleLinksToSameNode()
{
	printTestHeader("Test Stress: Multiple Links To Same Node");
	Shell sh;
	sh.vi("original", 5000);
	for (int i = 0; i < 30; i++)
	{
		sh.ln("original", "link" + to_string(i));
	}

	// All should point to same node
	for (int i = 0; i < 30; i++)
	{
		assert(sh.stat("link" + to_string(i)).find("5000 Bytes") != string::npos);
	}
	printTestResult(true);
}

void testStressRemoveAllFiles()
{
	printTestHeader("Test Stress: Remove All Files");
	Shell sh;
	for (int i = 0; i < 50; i++)
	{
		sh.vi("file" + to_string(i), i * 100);
	}

	for (int i = 0; i < 50; i++)
	{
		sh.rm("file" + to_string(i));
	}

	string ls_output = sh.ls();
	// Should be empty or just have reset color codes
	assert(ls_output.find("file0") == string::npos);
	printTestResult(true);
}

void testStressFileModification()
{
	printTestHeader("Test Stress: File Modification Over Time");
	Shell sh;
	sh.vi("file", 100);

	for (int i = 0; i < 50; i++)
	{
		sh.vi("file", 100 + i * 50);
		string stat_output = sh.stat("file");
		assert(stat_output.find(to_string(100 + i * 50)) != string::npos);
	}
	printTestResult(true);
}

// ======================= EDGE CASES =======================

void testEdgeCaseEmptyPathNames()
{
	printTestHeader("Test Edge Case: Path with consecutive slashes");
	Shell sh;
	sh.mkdir("a");
	sh.cd("//a///"); // Should be same as cd("a")
	assert(sh.pwd() == "/a");
	printTestResult(true);
}

void testEdgeCaseRelativeAbsoluteMix()
{
	printTestHeader("Test Edge Case: Mix Relative and Absolute Paths");
	Shell sh;
	sh.mkdir("a");
	sh.mkdir("b");
	sh.cd("a");
	assert(sh.pwd() == "/a");
	sh.cd("../b");
	assert(sh.pwd() == "/b");
	sh.cd("/a");
	assert(sh.pwd() == "/a");
	printTestResult(true);
}

void testEdgeCaseLargeFileSizes()
{
	printTestHeader("Test Edge Case: Large File Sizes");
	Shell sh;
	sh.vi("huge", 999999999);
	string stat_output = sh.stat("huge");
	assert(stat_output.find("999999999") != string::npos);
	printTestResult(true);
}

void testEdgeCaseDirectorySizeWithMultipleFiles()
{
	printTestHeader("Test Edge Case: Directory Size Calculation");
	Shell sh;
	sh.mkdir("dir");
	sh.cd("dir");
	int total = 0;
	for (int i = 0; i < 10; i++)
	{
		int size = (i + 1) * 100;
		sh.vi("f" + to_string(i), size);
		total += size;
	}
	sh.cd("/");
	string stat_output = sh.stat("dir");
	assert(stat_output.find(to_string(total)) != string::npos);
	printTestResult(true);
}

void testEdgeCaseSpecialCharactersInNames()
{
	printTestHeader("Test Edge Case: Special Characters In Names");
	Shell sh;
	sh.vi("file-name_123", 100);
	sh.mkdir("dir.name");
	string ls_output = sh.ls();
	assert(ls_output.find("file-name_123") != string::npos);
	assert(ls_output.find("dir.name") != string::npos);
	printTestResult(true);
}

// ======================= MAIN TEST RUNNER =======================

int main()
{
	cout << "\n"
		 << GREEN << "╔════════════════════════════════════════════════════════════╗\n"
		 << "║         COMPREHENSIVE SHELL FILESYSTEM TESTS SUITE           ║\n"
		 << "║                  PRACTICA-4 TEST SUITE                       ║\n"
		 << "╚════════════════════════════════════════════════════════════╝" << RESET << "\n";

	try
	{
		// Test Group 1: Basic Commands
		cout << "\n"
			 << GREEN << "▶ GROUP 1: BASIC COMMANDS" << RESET << "\n";
		testPwdInitial();
		testLsInitial();
		testDuInitial();

		// Test Group 2: File Creation with VI
		cout << "\n"
			 << GREEN << "▶ GROUP 2: FILE CREATION (VI)" << RESET << "\n";
		testViCreateSimpleFile();
		testViCreateMultipleFiles();
		testViModifyExistingFile();
		testViVariousSizes();
		testViZeroSize();
		testViInvalidNameWithSlash();
		testViInvalidNameDot();
		testViInvalidNameDotDot();

		// Test Group 3: Directory Creation (MKDIR)
		cout << "\n"
			 << GREEN << "▶ GROUP 3: DIRECTORY CREATION (MKDIR)" << RESET << "\n";
		testMkdirBasic();
		testMkdirMultipleDirs();
		testMkdirAlreadyExists();
		testMkdirInvalidNameWithSlash();
		testMkdirInvalidNameDot();
		testMkdirInvalidNameDotDot();

		// Test Group 4: Navigation (CD)
		cout << "\n"
			 << GREEN << "▶ GROUP 4: NAVIGATION (CD)" << RESET << "\n";
		testCdToCreatedDir();
		testCdMultipleLevels();
		testCdDotDot();
		testCdAbsolutePath();
		testCdRelativePath();
		testCdRoot();
		testCdNonexistentPath();
		testCdToFile();
		testCdAboveRoot();
		testCdDotDotAtRoot();
		testCdComplexPath();

		// Test Group 5: STAT Command
		cout << "\n"
			 << GREEN << "▶ GROUP 5: STAT COMMAND" << RESET << "\n";
		testStatFile();
		testStatDirectory();
		testStatDirectoryWithFiles();
		testStatAbsolutePath();
		testStatRelativePath();
		testStatNonexistent();
		testStatDeeplyNestedDirectory();

		// Test Group 6: Links (LN)
		cout << "\n"
			 << GREEN << "▶ GROUP 6: LINKS (LN)" << RESET << "\n";
		testLnCreateSimpleLink();
		testLnLinkToDirectory();
		testLnAccessThroughLink();
		testLnCdThroughLink();
		testLnMultipleLinksToSame();
		testLnAbsolutePath();
		testLnRelativePath();
		testLnNameAlreadyExists();
		testLnInvalidName();
		testLnNonexistentTarget();
		testLnCircularReference();
		testLnDeepCircularReference();
		testLnCreateLinkToDotDot();

		// Test Group 7: Removal (RM)
		cout << "\n"
			 << GREEN << "▶ GROUP 7: REMOVAL (RM)" << RESET << "\n";
		testRmFile();
		testRmDirectory();
		testRmDirectoryWithContents();
		testRmLink();
		testRmNonexistent();
		testRmRoot();
		testRmAbsolutePath();
		testRmRelativePath();
		testRmFromDirectory();
		testRmCdThroughLink();
		testRmMultipleLinksLastRemains();

		// Test Group 8: DU Command
		cout << "\n"
			 << GREEN << "▶ GROUP 8: DU COMMAND" << RESET << "\n";
		testDuEmpty();
		testDuWithFiles();
		testDuWithDirectories();
		testDuMixed();

		// Test Group 9: LS Command
		cout << "\n"
			 << GREEN << "▶ GROUP 9: LS COMMAND" << RESET << "\n";
		testLsAfterViCreation();
		testLsAfterMkdir();
		testLsWithLinks();
		testLsInSubdirectory();

		// Test Group 10: Complex Scenarios
		cout << "\n"
			 << GREEN << "▶ GROUP 10: COMPLEX SCENARIOS" << RESET << "\n";
		testComplexScenarioDeepStructure();
		testComplexScenarioMultipleLinks();
		testComplexScenarioLinkToDirectoryNavigation();
		testComplexScenarioMixedOperations();
		testComplexScenarioRmWithLinks();
		testComplexScenarioPathResolution();
		testComplexScenarioPwdAfterOperations();

		// Stress Tests
		cout << "\n"
			 << GREEN << "▶ STRESS TESTS" << RESET << "\n";
		testStressCreateMany();
		testStressCreateDeepNesting();
		testStressMultipleLinksToSameNode();
		testStressRemoveAllFiles();
		testStressFileModification();

		// Edge Cases
		cout << "\n"
			 << GREEN << "▶ EDGE CASES" << RESET << "\n";
		testEdgeCaseEmptyPathNames();
		testEdgeCaseRelativeAbsoluteMix();
		testEdgeCaseLargeFileSizes();
		testEdgeCaseDirectorySizeWithMultipleFiles();
		testEdgeCaseSpecialCharactersInNames();
	}
	catch (const exception &e)
	{
		cout << RED << "\nUnexpected exception: " << e.what() << RESET << "\n";
		return 1;
	}

	cout << "\n"
		 << GREEN << "╔════════════════════════════════════════════════════════════╗\n"
		 << "║                  ALL TESTS COMPLETED SUCCESSFULLY!           ║\n"
		 << "║              Every test case has been validated!             ║\n"
		 << "╚════════════════════════════════════════════════════════════╝" << RESET << "\n\n";

	return 0;
}
