/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//

import junit.framework.TestCase;
import java.util.Random;
import java.security.SecureRandom;


/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false; //passStatus and failStatus control pass/fail messages separately
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   //TRUE = print
   private boolean passStatus = false;
   private boolean failStatus = true;

   public UrlValidatorTest(String testName) {
      super(testName);
}



   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

     // Expected: pass     Result: fail
     System.out.println(urlVal.isValid("http://www.amazon.com:65535"));

     // Expected: pass     Result: fail
     System.out.println(urlVal.isValid("http://www.amazon.com:6553"));

     // Expected: pass     Result: pass
     System.out.println(urlVal.isValid("http://www.amazon.com:655"));

     // Expected: pass     Result: pass
     System.out.println(urlVal.isValid("http://www.amazon.com:65"));

     // Expected: pass     Result: pass
     System.out.println(urlVal.isValid("http://www.amazon.com:6"));

     // Expected: fail     Result: fail
     System.out.println(urlVal.isValid("http://www.amazon.com:"));


     //GRACE ADDED
     //Expected: Valid 	Result: Valid
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   //Expected: Invalid	Result: Invalid
	   System.out.println(urlVal.isValid("http://https://www.amazon.com"));
	   //Expected: Invalid	Result: Invalid
	   System.out.println(urlVal.isValid("http://www.ama/zon.com"));
	   //Expected: Valid	Result: Valid
	   System.out.println(urlVal.isValid("http://amazon.org"));
	   //Expected: Invalid	Result: Invalid
	   System.out.println(urlVal.isValid("http://www.a?mazon.com"));
	   //Expected: Valid	Result: Valid
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   //Expected: Invalid	Result: Valid
	   System.out.println(urlVal.isValid("http://2.2.2.255"));
	   //Expected: Invalid	Result: Valid
	   System.out.println(urlVal.isValid("http://2.2.2.256"));
	   //Expected: Invalid	Result: Valid
	   System.out.println(urlVal.isValid("http://2.2.2.895"));
     //Expected: Valid	Result: Valid
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   //Expected: Valid	Result: Invalid
	   System.out.println(urlVal.isValid("http://www.amazon.com?x=1"));
	   //Expected: Valid	Result: Invalid
	   System.out.println(urlVal.isValid("http://www.amazon.com?x"));
	   //Expected: Invalid	Result: Valid
	   System.out.println(urlVal.isValid("http://www.amazon.com?x\n"));
	   //Expected: Valid	Result: Invalid
	   System.out.println(urlVal.isValid("http://www.amazon.com?x\0"));

   }

   public boolean testPart(UrlValidator urlVal, String testUrl)
   {
	   return urlVal.isValid(testUrl);
   }

   public void passMessage(String testUrl)
   {
	   System.out.println("PASSED: " + testUrl);
   }

   public void failMessage(String testUrl)
   {
	   System.out.println("FAILED: " + testUrl);
   }


   /*Using https://en.wikipedia.org/wiki/Uniform_Resource_Identifier to build
    * valid URLs
    */
   public void testYourFirstPartition(){
	   int test = 0;
	   int pass = 0;
	   String append = "";
	   String prepend = "www.google.com";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   String[] valid = {"http://",
			   			 "ftp://",
			   			 "h3t://",
			   			 "file://",

			   			 ""};

	   String[] invalid = {"htp:",
			   	   		   "http:/",
			   	   		   "http//",
			   	   		   "http:///",
			   	   		   "://"};

	   System.out.println("-----Testing Valid Scheme-----");

	   for (int i = 0; i < valid.length; i++) {
		   test++;

		   //valid schemes pass as valid
		   if (testPart(urlVal, append + valid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + valid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + valid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("-----Testing Invalid Scheme-----");

	   for (int i = 0; i < invalid.length; i++) {
		   test++;

		   //invalid schemes pass as invalid
		   if (!testPart(urlVal, append + invalid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + invalid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + invalid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("[" + pass + "/" + test + " SCHEMES passed]");
   }

   public void testYourSecondPartition(){
	   int test = 0;
	   int pass = 0;
	   String append = "http://";
	   String prepend = "";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   String[] valid = {"amazon.com",
			   			 "google.com",
			   			 "google.ca",
			   			 "0.0.0.0",
			   			 "255.255.255.255"
			   			 };

	   String[] invalid = {"256.256.256.256",
			   			   "1.2.3.4.5",
			   			   "-1.-1.-1.-1",
			   			   ".com",
			   			   ".ca",
			   			   ""};

	   System.out.println("-----Testing Valid Authority-----");

	   for (int i = 0; i < valid.length; i++) {
		   test++;

		   //valid authorities pass as valid
		   if (testPart(urlVal, append + valid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + valid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + valid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("-----Testing Invalid Authority-----");

	   for (int i = 0; i < invalid.length; i++) {
		   test++;

		   //invalid authorities pass as invalid
		   if (!testPart(urlVal, append + invalid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + invalid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + invalid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("["+ pass + "/" + test + " AUTHORITIES PASSED]");
   }

   public void testYourThirdPartition(){
	   int test = 0;
	   int pass = 0;
	   String append = "http://www.google.com";
	   String prepend = "";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   /*per https://en.wikipedia.org/wiki/Port_%28computer_networking%29
	    * ports should range from 0 to 65535 inclusive
	    */
	   String[] valid = {":80",
			   			 ":65535",
			   			 ":0",
			   			 ":100",
			   			 ":1000",
			   			 ""};


	   String[] invalid = {":-1",
			   			   ":65a",
			   			   ":65636",
			   			   ":aa"};

	   System.out.println("-----Testing Valid Port-----");

	   for (int i = 0; i < valid.length; i++) {
		   test++;

		   //valid ports pass as valid
		   if (testPart(urlVal, append + valid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + valid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + valid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("-----Testing Invalid Port-----");

	   for (int i = 0; i < invalid.length; i++) {
		   test++;

		   //invalid ports pass as invalid
		   if (!testPart(urlVal, append + invalid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + invalid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + invalid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("["+ pass + "/" + test + " PORTS PASSED]");
   }

   public void testYourFourthPartition(){
	   int test = 0;
	   int pass = 0;
	   String append = "http://www.google.com";
	   String prepend = "";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   String[] valid = {"/test1",
			   			 "/123",
			   			 "/$23",
			   			 "/te!2",
			   			 "/test1/",
			   			 ""};

	   String[] invalid = {"/..",
			   			   "/../",
			   			   "/..//file",
			   			   "/test1//file",
			   			   "//test1/file",
			   			   "//.",
			   			   "//.//"};

	   System.out.println("-----Testing Valid Path-----");

	   for (int i = 0; i < valid.length; i++) {
		   test++;

		   //valid authorities pass as valid
		   if (testPart(urlVal, append + valid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + valid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + valid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("-----Testing Invalid Path-----");

	   for (int i = 0; i < invalid.length; i++) {
		   test++;

		   //invalid authorities pass as invalid
		   if (!testPart(urlVal, append + invalid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + invalid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + invalid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("["+ pass + "/" + test + " PATHS PASSED]");
   }

   public void testYourFifthPartition(){
	   int test = 0;
	   int pass = 0;
	   String append = "http://www.google.com";
	   String prepend = "";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_2_SLASHES + UrlValidator.NO_FRAGMENTS);

	   String[] valid = {"/test1",
			   			 "/123",
			   			 "/$23",
			   			 "/te!2",
			   			 "/test1/",
			   			"/test1//file",
			   			 ""};

	   String[] invalid = {"/..",
			   			   "/../",
			   			   "/..//file",
			   			   "/#//file",
			   			   "//test1/file",
			   			   "//."};

	   System.out.println("-----Testing Valid Option-----");

	   for (int i = 0; i < valid.length; i++) {
		   test++;

		   //valid authorities pass as valid
		   if (testPart(urlVal, append + valid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + valid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + valid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("-----Testing Invalid Option-----");

	   for (int i = 0; i < invalid.length; i++) {
		   test++;

		   //invalid authorities pass as invalid
		   if (!testPart(urlVal, append + invalid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + invalid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + invalid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("["+ pass + "/" + test + " OPTIONS PASSED]");
   }

   public void testYourSixthPartition(){
	   int test = 0;
	   int pass = 0;
	   String append = "http://www.google.com";
	   String prepend = "";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   String[] valid = {"?action=view",
			   			 "?action=edit&mode=up",
			   			 "?action=edit;mode=up",
			   			 ""};

	   String[] invalid = {"@action=view",
			   			   "&action=view",
			   			   "!action=view"};

	   System.out.println("-----Testing Valid Query-----");

	   for (int i = 0; i < valid.length; i++) {
		   test++;

		   //valid authorities pass as valid
		   if (testPart(urlVal, append + valid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + valid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + valid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("-----Testing Invalid Query-----");

	   for (int i = 0; i < invalid.length; i++) {
		   test++;

		   //invalid authorities pass as invalid
		   if (!testPart(urlVal, append + invalid[i] + prepend))
		   {
			   pass++;
			   if (passStatus)
			   {
				   passMessage(append + invalid[i] + prepend);
			   }
		   }
		   else
		   {
			   if (failStatus)
			   {
				   failMessage(append + invalid[i] + prepend);
			   }
		   }
	   }

	   System.out.println("["+ pass + "/" + test + " QUERIES PASSED]");
   }


   public void testIsValid()
   {
	   System.out.println("         [Base Testing Starts]         ");
	   //random seeds
	   Random random = new Random();

	   //url true/false indicator
	   String trueTestURL = "";
	   String falseTestURL = "";
	   UrlValidator trueValidator;
	   UrlValidator falseValidator;

	   //change this to 10000
	   for (int i = 0; i < 10000; i++)
	   {
		   int trueSchemeNum = random.nextInt(5);
		   int falseSchemeNum = random.nextInt(5);
		   int trueAuthorityNum = random.nextInt(7);
		   int falseAuthorityNum = random.nextInt(12);
		   int truePortNum = random.nextInt(5);
		   int falsePortNum = random.nextInt(2);
		   int truePathNum = random.nextInt(9);
		   int falsePathNum = random.nextInt(6);
		   int trueQueryNum = random.nextInt(3);

		   //generates true urls
		   trueTestURL = trueTestUrlScheme[trueSchemeNum] + trueTestUrlAuthority[trueAuthorityNum] +
				   trueTestUrlPort[truePortNum] + trueTestPath[truePathNum] + trueTestUrlQuery[trueQueryNum];

		   //generates false urls
		   falseTestURL = falseTestUrlScheme[falseSchemeNum] + falseTestUrlAuthority[falseAuthorityNum] +
				   falseTestUrlPort[falsePortNum] + falseTestPath[falsePathNum];

		   //true validator
		   trueValidator = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		   trueValidator.isValid(trueTestURL);

		   //false validator
		   falseValidator = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		   falseValidator.isValid(falseTestURL);


		   //test true urls
		   System.out.println(" ----- Testing True URLS ----- ");
		   boolean trueBugCount = trueValidator.isValid(trueTestURL);
		   if (trueBugCount) {
			   System.out.println("TEST PASS!");
//			   System.out.println("URL PASS: " + trueTestURL);
		   } else {
			   // if test fails print the count and the particular URL that failed
			   System.out.println("TEST FAIL!");
			   System.out.println("URL Fail: " + trueTestURL);
			   System.out.println("Actual: " + trueBugCount + " | Expected: true");
		   }

		   //test false urls
		   System.out.println(" ----- Testing False URLS ----- ");
		   boolean falseBugCount = falseValidator.isValid(falseTestURL);
		   if (!falseBugCount) {
			   System.out.println("TEST PASS!");
//			   System.out.println("URL PASS: " + falseTestURL);
		   } else {
			   System.out.println("URL Fail: " + falseTestURL);
			   System.out.println("Actual: " + falseBugCount + " | Expected: false");
		   }
	   }
	   System.out.println("          [Base Testing Ended]            ");
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */

   String[] trueTestUrlScheme = {
		   "http://",
		   "ftp://",
		   "https://",
		   "h3t://",
		   ""
		  };

   String[] falseTestUrlScheme = {
		   "3ht://",
		   "http:/",
		   "http:",
		   "http/",
		   "://"
		  };

   String[] trueTestUrlAuthority = {
		   "www.google.com",
		   "go.com",
		   "go.au",
		   "0.0.0.0",
		   "255.255.255.255",
		   "255.com",
		   "go.cc"
		  };

   String[] falseTestUrlAuthority = {
		   "256.256.256.256",
		   "1.2.3.4.5",
		   "1.2.3.4.",
		   "1.2.3",
		   ".1.2.3.4",
		   "go.a",
		   "go.a1a",
		   "go.1aa",
		   "aaa.",
		   ".aaa",
		   "aaa",
		   ""
		  };

   String[] trueTestUrlPort = {
		   ":80",
		   ":65535",
		   ":0",
		   "",
		   ":65636"
		  };

   String[] falseTestUrlPort = {
		   ":-1",
		   ":65a"
		  };

   String[] trueTestPath = {
		   "/test1",
		   "/t123",
		   "/$23",
		   "/test1/",
		   "",
		   "/test1/file",
		   "/t123/file",
		   "/$23/file",
		   "/test1//file"
		  };
   String[] falseTestPath = {
		   "/..",
		   "/../",
		   "/#",
		   "/../file",
		   "/..//file",
		   "/#/file"
		  };
   String[] trueTestUrlQuery = {
		   "?action=view",
		   "?action=edit&mode=up",
		   ""
		  };


   public void testAnyOtherUnitTest()
   {
	   //check for a functioning URL port
	   	System.out.println("Any Other Unit Testing Starts");
	   	SecureRandom random = new SecureRandom();
	   	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   	int RandomNumber;
	   	//change this to 10000 before submission
	   	for(int i = 0;i<10000;i++)
	   	{
	   		RandomNumber = random.nextInt(10000) + 1;
	   		//System.out.println("http://www.google.com:"+ RandomNumber);
	   		System.out.println(urlVal.isValid("http://www.google.com:"+ RandomNumber)) ;
	   	}
	   	System.out.println("Any Other Unit Testing Ended");
   }
}
