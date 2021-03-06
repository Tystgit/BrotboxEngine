#pragma once

#include "String.h"
#include <iostream>
#include <string>
#include "UtilTest.h"

namespace bbe {
	namespace test {
		void testString() {

			//TODO add non SSO Tests

			bbe::String emptyString;
			bbe::String stringWChar  (L"Hallo WChar");
			bbe::String stringClassic("Hallo Classic");
			bbe::String stringStd(std::string("Hallo STD!"));
			bbe::String stringStdw(std::string("Hallo WSTD!"));
			bbe::String stringNumber(2839.192);

			bbe::String stringCopyConstructor(stringWChar);
			bbe::String stringMovedFrom("I will be moved!");
			bbe::String stringMovedTo(std::move(stringMovedFrom));

			bbe::String stringAssignmentFrom("I will be assigned!");
			bbe::String stringAssignmentTo("");
			stringAssignmentTo = stringAssignmentFrom;

			bbe::String stringMoveAssignmentFrom("I will be move-assigned!");
			bbe::String stringMoveAssignmentTo("");
			stringMoveAssignmentTo = std::move(stringMoveAssignmentFrom);

			assertEquals(emptyString.getLength()           , 0);
			assertEquals(stringWChar.getLength()           , 11);
			assertEquals(stringClassic.getLength()         , 13);
			assertEquals(stringStd.getLength()             , 10);
			assertEquals(stringStdw.getLength()            , 11);
			assertEquals(stringNumber.getLength()          , 11);
			assertEquals(stringCopyConstructor.getLength() , 11);
			assertEquals(stringMovedTo.getLength()         , 16);
			assertEquals(stringAssignmentFrom.getLength()  , 19);
			assertEquals(stringAssignmentTo.getLength()    , 19);
			assertEquals(stringMoveAssignmentTo.getLength(), 24);

			{
				bbe::String stringAdd1("con");
				bbe::String stringAdd2("cattttt");
				bbe::String stringAdd3 = stringAdd1 + stringAdd2;
				assertEquals(stringAdd3, "concattttt");
			}

			{
				bbe::String stringAdd0WOSSO("Kurz ");
				bbe::String stringAdd1WOSSO("Hallo Welt! Das ist ein langer Text! ");
				bbe::String stringAddr = stringAdd0WOSSO + stringAdd1WOSSO;
				assertEquals(stringAddr, "Kurz Hallo Welt! Das ist ein langer Text! ");
				bbe::String stringAdd2WOSSO("Und hierdurch wird er sogar noch l�nger!");
				bbe::String stringAdd3WOSSO = stringAdd1WOSSO + stringAdd2WOSSO;
				assertEquals(stringAdd3WOSSO, "Hallo Welt! Das ist ein langer Text! Und hierdurch wird er sogar noch l�nger!");
			}

			{
				bbe::String stringAdd1("con");
				bbe::String stringAdd2("");
				bbe::String stringAdd3 = stringAdd1 + stringAdd2;
				assertEquals(stringAdd3, "con");
			}

			{
				bbe::String stringAdd1("");
				bbe::String stringAdd2("con");
				bbe::String stringAdd3 = stringAdd1 + stringAdd2;
				assertEquals(stringAdd3, "con");
			}

			{
				bbe::String stringAdd1("con");
				std::string stringAdd2("cattttt");
				bbe::String stringAdd3 = stringAdd1 + stringAdd2;
				assertEquals(stringAdd3, "concattttt");
			}

			{
				bbe::String stringAdd1("con");
				std::wstring stringAdd2(L"cattttt");
				bbe::String stringAdd3 = stringAdd1 + stringAdd2;
				assertEquals(stringAdd3, "concattttt");
			}

			{
				bbe::String stringAdd1("con");
				bbe::String stringAdd3 = stringAdd1 + "cattttt";
				assertEquals(stringAdd3, "concattttt");
			}

			{
				bbe::String stringAdd1("con");
				bbe::String stringAdd3 = stringAdd1 + L"cattttt";
				assertEquals(stringAdd3, "concattttt");
			}

			{
				bbe::String stringAdd1("con");
				bbe::String stringAdd2("cattttt");
				bbe::String stringAdd3 = stringAdd2 + stringAdd1;
				assertEquals(stringAdd3, "catttttcon");
			}

			{
				bbe::String stringAdd1("con");
				std::string stringAdd2("cattttt");
				bbe::String stringAdd3 = stringAdd2 + stringAdd1;
				assertEquals(stringAdd3, "catttttcon");
			}

			{
				bbe::String stringAdd1("con");
				std::wstring stringAdd2(L"cattttt");
				bbe::String stringAdd3 = stringAdd2 + stringAdd1;
				assertEquals(stringAdd3, "catttttcon");
			}

			{
				bbe::String stringAdd1("con");
				bbe::String stringAdd3 = "cattttt" + stringAdd1;
				assertEquals(stringAdd3, "catttttcon");
			}

			{
				bbe::String stringAdd1("con");
				bbe::String stringAdd3 = L"cattttt" + stringAdd1;
				assertEquals(stringAdd3, "catttttcon");
			}


			{
				bbe::String s1("A");
				s1 += "B";
				assertEquals(s1, "AB");
				s1 += "C";
				assertEquals(s1, "ABC");
				s1 += "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"; // <- SSO Buster
				assertEquals(s1, "ABCLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
			}

			{
				bbe::String stringAddTest("con");
				stringAddTest += "cattt";
				assertEquals(stringAddTest, "concattt");
			}

			{
				bbe::String stringAddTest("con");
				stringAddTest += L"cattt";
				assertEquals(stringAddTest, "concattt");
			}

			{
				bbe::String stringAddTest("con");
				stringAddTest += std::string("cattt");
				assertEquals(stringAddTest, "concattt");
			}

			{
				bbe::String stringAddTest("con");
				stringAddTest += std::wstring(L"cattt");
				assertEquals(stringAddTest, "concattt");
			}

			{
				bbe::String stringAddTest("con");
				stringAddTest += String("cattt");
				assertEquals(stringAddTest, "concattt");
			}

			{
				bbe::String stringAddTest("con");
				stringAddTest += 17;
				assertEquals(stringAddTest, "con17");
			}
			
			{
				bbe::String stringTrim("   This is gonna get trimmed! :)          ");
				stringTrim.trim();
				assertEquals(stringTrim, "This is gonna get trimmed! :)");
			}

			{
				bbe::String stringTrim("   This is gonna get trimmed! :)");
				stringTrim.trim();
				assertEquals(stringTrim, "This is gonna get trimmed! :)");
			}

			{
				bbe::String stringTrim("This is gonna get trimmed! :)                      ");
				stringTrim.trim();
				assertEquals(stringTrim, "This is gonna get trimmed! :)");
			}

			{
				bbe::String stringTrim("This is gonna get trimmed! :)");
				stringTrim.trim();
				assertEquals(stringTrim, "This is gonna get trimmed! :)");
			}

			{
				bbe::String stringTrim("          ");
				stringTrim.trim();
				assertEquals(stringTrim, "");
			}

			{
				bbe::String countTest("Some stuff in this string will get counted! this is gonna be cool!");
				assertEquals(countTest.count(bbe::String("s")), 5);
				assertEquals(countTest.count(bbe::String("")), 0);
				assertEquals(countTest.count(bbe::String(" ")), 12);
				assertEquals(countTest.count(bbe::String("this")), 2);
				assertEquals(countTest.count(std::string("s")), 5);
				assertEquals(countTest.count(std::string("")), 0);
				assertEquals(countTest.count(std::string(" ")), 12);
				assertEquals(countTest.count(std::string("this")), 2);
				assertEquals(countTest.count(std::wstring(L"s")), 5);
				assertEquals(countTest.count(std::wstring(L"")), 0);
				assertEquals(countTest.count(std::wstring(L" ")), 12);
				assertEquals(countTest.count(std::wstring(L"this")), 2);
				assertEquals(countTest.count("s"), 5);
				assertEquals(countTest.count(""), 0);
				assertEquals(countTest.count(" "), 12);
				assertEquals(countTest.count("this"), 2);
				assertEquals(countTest.count(L"s"), 5);
				assertEquals(countTest.count(L""), 0);
				assertEquals(countTest.count(L" "), 12);
				assertEquals(countTest.count(L"this"), 2);
			}

			{
				bbe::String splitter("This string will be  splitted!");
				auto splitSpace = splitter.split(" ");
				assertEquals(splitSpace[0], "This");
				assertEquals(splitSpace[1], "string");
				assertEquals(splitSpace[2], "will");
				assertEquals(splitSpace[3], "be");
				assertEquals(splitSpace[4], "");
				assertEquals(splitSpace[5], "splitted!");
				assertEquals(splitSpace.getLength(), 6);

				auto splitTwoChar = splitter.split(" s");
				assertEquals(splitTwoChar[0], "This");
				assertEquals(splitTwoChar[1], "tring will be ");
				assertEquals(splitTwoChar[2], "plitted!");
				assertEquals(splitTwoChar.getLength(), 3);

				auto splitNotHappening = splitter.split("This is no part of the string");
				assertEquals(splitNotHappening[0], "This string will be  splitted!");
				assertEquals(splitNotHappening.getLength(), 1);
			}

			{
				bbe::String splitter("This string will be  splitted!");
				auto splitSpace = splitter.split(L" ");
				assertEquals(splitSpace[0], "This");
				assertEquals(splitSpace[1], "string");
				assertEquals(splitSpace[2], "will");
				assertEquals(splitSpace[3], "be");
				assertEquals(splitSpace[4], "");
				assertEquals(splitSpace[5], "splitted!");
				assertEquals(splitSpace.getLength(), 6);

				auto splitTwoChar = splitter.split(L" s");
				assertEquals(splitTwoChar[0], "This");
				assertEquals(splitTwoChar[1], "tring will be ");
				assertEquals(splitTwoChar[2], "plitted!");
				assertEquals(splitTwoChar.getLength(), 3);

				auto splitNotHappening = splitter.split(L"This is no part of the string");
				assertEquals(splitNotHappening[0], "This string will be  splitted!");
				assertEquals(splitNotHappening.getLength(), 1);
			}

			{
				bbe::String splitter("This string will be  splitted!");
				auto splitSpace = splitter.split(std::string(" "));
				assertEquals(splitSpace[0], "This");
				assertEquals(splitSpace[1], "string");
				assertEquals(splitSpace[2], "will");
				assertEquals(splitSpace[3], "be");
				assertEquals(splitSpace[4], "");
				assertEquals(splitSpace[5], "splitted!");
				assertEquals(splitSpace.getLength(), 6);

				auto splitTwoChar = splitter.split(std::string(" s"));
				assertEquals(splitTwoChar[0], "This");
				assertEquals(splitTwoChar[1], "tring will be ");
				assertEquals(splitTwoChar[2], "plitted!");
				assertEquals(splitTwoChar.getLength(), 3);

				auto splitNotHappening = splitter.split(std::string("This is no part of the string"));
				assertEquals(splitNotHappening[0], "This string will be  splitted!");
				assertEquals(splitNotHappening.getLength(), 1);
			}

			{
				bbe::String splitter("This string will be  splitted!");
				auto splitSpace = splitter.split(std::wstring(L" "));
				assertEquals(splitSpace[0], "This");
				assertEquals(splitSpace[1], "string");
				assertEquals(splitSpace[2], "will");
				assertEquals(splitSpace[3], "be");
				assertEquals(splitSpace[4], "");
				assertEquals(splitSpace[5], "splitted!");
				assertEquals(splitSpace.getLength(), 6);

				auto splitTwoChar = splitter.split(std::wstring(L" s"));
				assertEquals(splitTwoChar[0], "This");
				assertEquals(splitTwoChar[1], "tring will be ");
				assertEquals(splitTwoChar[2], "plitted!");
				assertEquals(splitTwoChar.getLength(), 3);

				auto splitNotHappening = splitter.split(std::wstring(L"This is no part of the string"));
				assertEquals(splitNotHappening[0], "This string will be  splitted!");
				assertEquals(splitNotHappening.getLength(), 1);
			}

			{
				bbe::String containString("This string will be analyzed if it contains various stuff");
				assertEquals(containString.contains(" "), true);
				assertEquals(containString.contains("will"), true);
				assertEquals(containString.contains("t c"), true);
				assertEquals(containString.contains("apple"), false);
				assertEquals(containString.contains("not contained"), false);
			}

			{
				bbe::String containString("This string will be analyzed if it contains various stuff");
				assertEquals(containString.contains(L" "), true);
				assertEquals(containString.contains(L"will"), true);
				assertEquals(containString.contains(L"t c"), true);
				assertEquals(containString.contains(L"apple"), false);
				assertEquals(containString.contains(L"not contained"), false);
			}

			{
				bbe::String containString("This string will be analyzed if it contains various stuff");
				assertEquals(containString.contains(std::string(" ")), true);
				assertEquals(containString.contains(std::string("will")), true);
				assertEquals(containString.contains(std::string("t c")), true);
				assertEquals(containString.contains(std::string("apple")), false);
				assertEquals(containString.contains(std::string("not contained")), false);
			}

			{
				bbe::String containString("This string will be analyzed if it contains various stuff");
				assertEquals(containString.contains(std::wstring(L" ")), true);
				assertEquals(containString.contains(std::wstring(L"will")), true);
				assertEquals(containString.contains(std::wstring(L"t c")), true);
				assertEquals(containString.contains(std::wstring(L"apple")), false);
				assertEquals(containString.contains(std::wstring(L"not contained")), false);
			}

			{
				bbe::String searchString("This string will be for searched through for various words!");
				assertEquals(searchString.search("This"), 0);
				assertEquals(searchString.search(""), 0);
				assertEquals(searchString.search("s"), 3);
				assertEquals(searchString.search("for"), 20);
				assertEquals(searchString.search("not contained"), -1);
			}

			{
				bbe::String searchString("This string will be for searched through for various words!");
				assertEquals(searchString.search(L"This"), 0);
				assertEquals(searchString.search(L""), 0);
				assertEquals(searchString.search(L"s"), 3);
				assertEquals(searchString.search(L"for"), 20);
				assertEquals(searchString.search(L"not contained"), -1);
			}

			{
				bbe::String searchString("This string will be for searched through for various words!");
				assertEquals(searchString.search(std::string("This")), 0);
				assertEquals(searchString.search(std::string("")), 0);
				assertEquals(searchString.search(std::string("s")), 3);
				assertEquals(searchString.search(std::string("for")), 20);
				assertEquals(searchString.search(std::string("not contained")), -1);
			}

			{
				bbe::String searchString("This string will be for searched through for various words!");
				assertEquals(searchString.search(std::wstring(L"This")), 0);
				assertEquals(searchString.search(std::wstring(L"")), 0);
				assertEquals(searchString.search(std::wstring(L"s")), 3);
				assertEquals(searchString.search(std::wstring(L"for")), 20);
				assertEquals(searchString.search(std::wstring(L"not contained")), -1);
			}

			{
				bbe::String searchString("This string will be for searched through for various words!");
				assertEquals(searchString.search(bbe::String("This")), 0);
				assertEquals(searchString.search(bbe::String(L"")), 0);
				assertEquals(searchString.search(bbe::String("s")), 3);
				assertEquals(searchString.search(bbe::String("for")), 20);
				assertEquals(searchString.search(bbe::String("not contained")), -1);
			}

			{
				bbe::String numberString("1928");
				assertEquals(numberString.toLong(), 1928);
				assertEquals(numberString.toDouble(), 1928);
				assertEquals(numberString.toFloat(), 1928);
			}

			{
				bbe::String numberString("1928.5");
				assertEquals(numberString.toLong(), 1928);
				assertEquals(numberString.toDouble(), 1928.5);
				assertEquals(numberString.toFloat(), 1928.5);
			}

			{
				bbe::String numberString("not a number");
				assertEquals(numberString.toLong(), 0);
				assertEquals(numberString.toDouble(), 0);
				assertEquals(numberString.toFloat(), 0);
			}

			{
				bbe::String numberString("number with offset 1282.5");
				assertEquals(numberString.toLong(), 0);
				assertEquals(numberString.toDouble(), 0);
				assertEquals(numberString.toFloat(), 0);
			}

			{
				bbe::String numberString("1282.5 number was at the beginning");
				assertEquals(numberString.toLong(), 1282);
				assertEquals(numberString.toDouble(), 1282.5);
				assertEquals(numberString.toFloat(), 1282.5);
			}

			{
				bbe::String numberString("     1282.5 number was at the beginning even space is okay");
				assertEquals(numberString.toLong(), 1282);
				assertEquals(numberString.toDouble(), 1282.5);
				assertEquals(numberString.toFloat(), 1282.5);
			}

			{
				bbe::String operatorString("working with operator[] :)");
				assertEquals(operatorString[1], L'o');
				assertEquals(operatorString[5], L'n');
				assertEquals(operatorString[7], L' ');
				assertEquals(operatorString[10], L't');
				assertEquals(operatorString[13], L'o');

				operatorString[4] = L'z';
				assertEquals(operatorString, "workzng with operator[] :)");
			}

			{
				bbe::String lowerUpperShifter("ThIs stRing will swiTCH BeTWeen lowER and UPPer cAse!");
				lowerUpperShifter.toLowerCase();
				assertEquals(lowerUpperShifter, "this string will switch between lower and upper case!");
				lowerUpperShifter.toLowerCase();
				assertEquals(lowerUpperShifter, "this string will switch between lower and upper case!");
				lowerUpperShifter.toUpperCase();
				assertEquals(lowerUpperShifter, "THIS STRING WILL SWITCH BETWEEN LOWER AND UPPER CASE!");
				lowerUpperShifter.toUpperCase();
				assertEquals(lowerUpperShifter, "THIS STRING WILL SWITCH BETWEEN LOWER AND UPPER CASE!");
				lowerUpperShifter.toLowerCase();
				assertEquals(lowerUpperShifter, "this string will switch between lower and upper case!");
				lowerUpperShifter.toUpperCase();
				assertEquals(lowerUpperShifter, "THIS STRING WILL SWITCH BETWEEN LOWER AND UPPER CASE!");
			}

			assertEquals(stringWChar, std::string("Hallo WChar"));
			assertEquals(std::string("Hallo WChar"), stringWChar);
			assertEquals(stringWChar, std::wstring(L"Hallo WChar"));
			assertEquals(std::wstring(L"Hallo WChar"), stringWChar);
			assertEquals(stringWChar, String(L"Hallo WChar"));
			assertEquals(String(L"Hallo WChar"), stringWChar);
			assertUnequals(stringWChar, std::string("Hallo Wshar"));
			assertUnequals(std::string("Hallo WCha!"), stringWChar);
			assertUnequals(stringWChar, std::wstring(L"Hajlo WChar"));
			assertUnequals(std::wstring(L"hallo WChar"), stringWChar);
			assertUnequals(stringWChar, String(L"Hallo WChaa"));
			assertUnequals(String(L"Haloo WChar"), stringWChar);

			assertEquals  (emptyString, "");
			assertEquals  ("", emptyString);
			assertUnequals(emptyString, "a");
			assertUnequals("a", emptyString);
			assertEquals  (emptyString, L"");
			assertEquals  (L"", emptyString);
			assertUnequals(emptyString, L"a");
			assertUnequals(L"a", emptyString);

			assertEquals  (stringWChar, "Hallo WChar");
			assertEquals  ("Hallo WChar", stringWChar);
			assertUnequals(stringWChar, "HalloWChar");
			assertUnequals("HalloWChar", stringWChar);
			assertEquals  (stringWChar, L"Hallo WChar");
			assertEquals  (L"Hallo WChar", stringWChar);
			assertUnequals(stringWChar, L"HalloWChar");
			assertUnequals(L"HalloWChar", stringWChar);

			assertEquals  (stringClassic, "Hallo Classic");
			assertEquals  ("Hallo Classic", stringClassic);
			assertUnequals(stringClassic, "HalloClassic");
			assertUnequals("HalloClassic", stringClassic);
			assertEquals  (stringClassic, L"Hallo Classic");
			assertEquals  (L"Hallo Classic", stringClassic);
			assertUnequals(stringClassic, L"HalloClassic");
			assertUnequals(L"HalloClassic", stringClassic);

			assertEquals  (stringStd, "Hallo STD!");
			assertEquals  ("Hallo STD!", stringStd);
			assertUnequals(stringStd, "HalloSTD!");
			assertUnequals("HalloSTD!", stringStd);
			assertEquals  (stringStd, L"Hallo STD!");
			assertEquals  (L"Hallo STD!", stringStd);
			assertUnequals(stringStd, L"HalloSTD!");
			assertUnequals(L"HalloSTD!", stringStd);

			assertEquals  (stringStdw, "Hallo WSTD!");
			assertEquals  ("Hallo WSTD!", stringStdw);
			assertUnequals(stringStdw, "HalloWSTD!");
			assertUnequals("HalloWSTD!", stringStdw);
			assertEquals  (stringStdw, L"Hallo WSTD!");
			assertEquals  (L"Hallo WSTD!", stringStdw);
			assertUnequals(stringStdw, L"HalloWSTD!");
			assertUnequals(L"HalloWSTD!", stringStdw);
			
			assertEquals  (stringNumber, "2839.192000");
			assertEquals  ("2839.192000", stringNumber);
			assertUnequals(stringNumber, "2839.392000");
			assertUnequals("2839.392000", stringNumber);
			assertEquals  (stringNumber, L"2839.192000");
			assertEquals  (L"2839.192000", stringNumber);
			assertUnequals(stringNumber, L"2839.392000");
			assertUnequals(L"2839.392000", stringNumber);

			assertEquals  (stringCopyConstructor, "Hallo WChar");
			assertEquals  ("Hallo WChar", stringCopyConstructor);
			assertUnequals(stringCopyConstructor, "HalloWChar");
			assertUnequals("HalloWChar", stringCopyConstructor);
			assertEquals  (stringCopyConstructor, L"Hallo WChar");
			assertEquals  (L"Hallo WChar", stringCopyConstructor);
			assertUnequals(stringCopyConstructor, L"HalloWChar");
			assertUnequals(L"HalloWChar", stringCopyConstructor);

			assertEquals  (stringMovedTo, "I will be moved!");
			assertEquals  ("I will be moved!", stringMovedTo);
			assertUnequals(stringMovedTo, "I willbe moved!");
			assertUnequals("I will b moved!", stringMovedTo);
			assertEquals  (stringMovedTo, L"I will be moved!");
			assertEquals  (L"I will be moved!", stringMovedTo);
			assertUnequals(stringMovedTo, L"I will be mved!");
			assertUnequals(L"I willbe moved!", stringMovedTo);

			assertEquals  (stringAssignmentTo, "I will be assigned!");
			assertEquals  ("I will be assigned!", stringAssignmentTo);
			assertUnequals(stringAssignmentTo, "I will be bssigned!");
			assertUnequals("I will be assjgned!", stringAssignmentTo);
			assertEquals  (stringAssignmentTo, L"I will be assigned!");
			assertEquals  (L"I will be assigned!", stringAssignmentTo);
			assertUnequals(stringAssignmentTo, L"I will be ssigned!");
			assertUnequals(L"I will be assigned", stringAssignmentTo);

			assertEquals  (stringAssignmentFrom, "I will be assigned!");
			assertEquals  ("I will be assigned!", stringAssignmentFrom);
			assertUnequals(stringAssignmentFrom, "I will be bssigned!");
			assertUnequals("I will be assjgned!", stringAssignmentFrom);
			assertEquals  (stringAssignmentFrom, L"I will be assigned!");
			assertEquals  (L"I will be assigned!", stringAssignmentFrom);
			assertUnequals(stringAssignmentFrom, L"I will be ssigned!");
			assertUnequals(L"I will be assigned", stringAssignmentFrom);

			assertEquals  (stringMoveAssignmentTo, "I will be move-assigned!");
			assertEquals  ("I will be move-assigned!", stringMoveAssignmentTo);
			assertUnequals(stringMoveAssignmentTo, "I will be move-assgned!");
			assertUnequals("I will be move-assignd!", stringMoveAssignmentTo);
			assertEquals  (stringMoveAssignmentTo, L"I will be move-assigned!");
			assertEquals  (L"I will be move-assigned!", stringMoveAssignmentTo);
			assertUnequals(stringMoveAssignmentTo, L"I will be moveassigned!");
			assertUnequals(L"I will be move-asigned!", stringMoveAssignmentTo);
		}
	}
}