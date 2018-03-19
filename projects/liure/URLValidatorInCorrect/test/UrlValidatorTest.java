/*****************************************************
 *    CS362: Software Engineering II
 *    Oregon State Univerisity
 *    Date: 2/18/2018
 *
 *    Final Project Part B: UrlValidator.isValid()
 *    Submitted by:
 *       Albert Nim
 *       Armand Parajon
 *       Reed Liu
 *****************************************************/
import junit.framework.TestCase;
import java.util.Random;

public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   /*********************************************** BEGIN MANUAL TESTING */
   public void testManualTest()
   {
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      System.out.println("MANUAL TESTS:");
      System.out.println("Expected to be true: ");
      System.out.println(urlVal.isValid("www.google.com"));
      //System.out.println(urlVal.isValid("ftp://www.youtube.com"));
      //System.out.println(urlVal.isValid("https://www.google.com"));
      System.out.println(urlVal.isValid("http://www.125.com"));
      System.out.println(urlVal.isValid("http://www.google.com:1"));
      System.out.println(urlVal.isValid("www.google.com:1"));
      System.out.println(urlVal.isValid("http://www.google.com:123"));
      System.out.println(urlVal.isValid("http://www.google.com:3234"));
      System.out.println(urlVal.isValid("http://oregonstate.edu"));
      System.out.println(urlVal.isValid("http://192.168.1.1"));
      System.out.println(urlVal.isValid("http://www.google.com/mail"));
      System.out.println(urlVal.isValid("http://www.google.com/mail/test"));
      System.out.println("----------------------------------------------------");
      
      //The ones listed here are all invalid URLs
      System.out.println("Expected to be false: ");
      System.out.println(urlVal.isValid("http://www.#!~+`=>@@#%google#.com"));
      System.out.println(urlVal.isValid("://www.google.com"));
      //System.out.println(urlVal.isValid("tp://www.google.com:"));
      System.out.println(urlVal.isValid("http:/www.google.com:"));
      System.out.println(urlVal.isValid("http://"));
      System.out.println(urlVal.isValid("randomstring"));
      System.out.println(urlVal.isValid("http://900.3000.1.3232"));
      System.out.println(urlVal.isValid("http://www.google.com///mail"));
      System.out.println(urlVal.isValid("http://www.google.comsdasdsadasd"));
      System.out.println(urlVal.isValid("http://www.google.com/ mail"));
      System.out.println(urlVal.isValid("http://www.google.asdf"));
      System.out.println("");

   }
   /*********************************************** BEGIN PARTITION TESTING */
   // Test partition: scheme
   public void testSchemePartition() {

      System.out.println("PARTITION TESTING: Scheme Partition.");
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);

      String testString = "www.amazon.com";

      ResultPair[] schemePairs = {new ResultPair("http://", true),
              new ResultPair("https", false),
              new ResultPair("3://", false),
              new ResultPair("://", false),
              new ResultPair(" ", true),
              new ResultPair("http://", true)};  // BUG: found when using scheme other than http://

      for (int i = 0; i < schemePairs.length; i++) {
         String testUrl = schemePairs[i].item + testString;
         boolean testValid = !schemePairs[i].valid;
         if (testValid == urlVal.isValid(testUrl)) {
            System.out.println("PASS: " + schemePairs[i].item + testString + " is " + testValid);
         } else
            System.out.println("FAIL: " + schemePairs[i].item + testString);
      }

      System.out.println("\n");
   }

   // Test partition: authority
   public void testAuthPartition() {
      System.out.println("PARTITION TESTING: Authority Partition.");
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS + UrlValidator.ALLOW_LOCAL_URLS);

      String beforeAuth = "http://";

      ResultPair[] authPairs = {new ResultPair("www.amazon.com", true),
              new ResultPair("amazon.com", true),
              new ResultPair("z.com", true),
              new ResultPair(".com", false),
              new ResultPair("//", false),
              new ResultPair("amazon.", false),
              new ResultPair("255.255.255.255", true),
              new ResultPair("300.300.300.300", false),
              new ResultPair("0.0.0.0", true),
              new ResultPair("1.1.1.1.1", false),
              new ResultPair("?.com", false),
              new ResultPair("a.a.a.a.a.a.a", false),
              new ResultPair("localhost", true),
              new ResultPair("www.?=.com", false)};
      // Regex seems to be invalid for numbers greater than 255, for multiple . symbols past 2,
      // and for illegal symbols ? and =.

      for (int i = 0; i < authPairs.length; i++) {
         String testUrl = beforeAuth + authPairs[i].item;
         boolean testValid = !authPairs[i].valid;
         if (testValid == urlVal.isValid(testUrl)) {
            System.out.println("PASS: " + testUrl + " is " + testValid);
         }
         else {
            System.out.println("FAIL: " + testUrl);
         }
      }

      System.out.println("\n");
   }

   // Test partition: path
   public void testPathPartition() {

      System.out.println("PARTITION TESTING: Path Partition.");
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS + UrlValidator.ALLOW_LOCAL_URLS);

      String beforeAuth = "http://www.amazon.com";

      ResultPair[] pathPairs = {new ResultPair("/home", true),
              new ResultPair("/home/index", true),
              new ResultPair("/home/index/", true),
              new ResultPair("/home/index.html", true),
              new ResultPair("/\\", false),
              new ResultPair(" ", true),
              new ResultPair("/home//", false),
              new ResultPair("/home/index.html//", false),
              new ResultPair("/..", false)};

      for (int i = 0; i < pathPairs.length; i++) {
         String testUrl = beforeAuth + pathPairs[i].item;
         boolean testValid = !pathPairs[i].valid;
         if (testValid == urlVal.isValid(testUrl)) {
            System.out.println("PASS: " + testUrl + " is " + testValid);
         }
         else {
            System.out.println("FAIL: " + testUrl);
         }
      }

      System.out.println("\n");
   }


   /******************************************************** BEGIN UNIT TESTING */
   //Test if correct domain name URLs are valid
   public void testIsValidCorrectUrlsDNS()
   {
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      int testCount = 2000;
      int passCount = 0;
      String[] randomDomains = generateRandomWords(testCount);
      String[] randomCorrectPrefixes = generateRandomCorrectPrefixes(testCount);
      String[] randomCorrectEndings = generateRandomCorrectEndings(testCount);

      for (int i = 0; i < testCount; i++) {
         String testUrl = randomCorrectPrefixes[i] + randomDomains[i] + randomCorrectEndings[i];

         if (urlVal.isValid(testUrl)) {
            //System.out.println(testUrl + " PASS"); //uncomment to show url
            passCount++;
         }
         else {
            //System.out.println(testUrl + " FAIL"); //uncomment to show url
         }
      }
      String resultString = String.format("UNIT TEST (CORRECT URLS): %d of %d tests passed.", passCount, testCount);
      System.out.println(resultString + "\n");
   }

   //Test if correct domain name URLs are valid
   public void testIsValidIncorrectUrlsDNS()
   {
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      int testCount = 2000;
      int passCount = 0;
      String[] randomDomains = generateRandomWords(testCount);
      String[] randomCorrectPrefixes = generateRandomCorrectPrefixes(testCount); //incorrect prefixes crash the program
      String[] randomIncorrectEndings = generateRandomIncorrectEndings(testCount);

      for (int i = 0; i < testCount; i++) {
         String testUrl = randomCorrectPrefixes[i] + randomDomains[i] + randomIncorrectEndings[i];

         //URL should be invalid
         if (!urlVal.isValid(testUrl)) {
            passCount++;
            //System.out.println(testUrl + " PASS"); //uncomment to show url
         }
         else {
            //System.out.println(testUrl + " FAIL"); //uncomment to show url
         }
      }

      String resultString = String.format("UNIT TEST (INCORRECT URLS): %d of %d tests passed.", passCount, testCount);
      System.out.println(resultString + "\n");

   }

   public static String[] generateRandomWords(int numberOfWords)
   {
      String[] randomStrings = new String[numberOfWords];
      Random rand = new Random();
      for(int i = 0; i < numberOfWords; i++)
      {
         char[] word = new char[rand.nextInt(8)+3]; // words of length 3 through 10. (1 and 2 letter words are boring.)
         for(int j = 0; j < word.length; j++)
         {
            word[j] = (char)('a' + rand.nextInt(26));
         }
         randomStrings[i] = new String(word);
      }
      return randomStrings;
   }

   public static String[] generateRandomCorrectPrefixes(int numberOfPrefixes){
      String[] randomPrefixes = new String[numberOfPrefixes];
      String[] correctPrefixes = {"http://www.", "http://www.", "www.", ""}; //note: adding FTP makes the function crash
      //String[] correctPrefixes = {"http://www.", "http://www.", "www.", "FTP://", ""};
      Random rand = new Random();
      for (int i = 0; i < numberOfPrefixes; i++) {
         randomPrefixes[i] = correctPrefixes[rand.nextInt(correctPrefixes.length)];
      }
      return randomPrefixes;
   }

   public static String[] generateRandomCorrectEndings(int numberOfEndings){
      String[] randomEndings = new String[numberOfEndings];
      String[] correctEndings = {".com", ".com/test", ".com/test/test2", ".au"};
      Random rand = new Random();
      for (int i = 0; i < numberOfEndings; i++) {
         randomEndings[i] = correctEndings[rand.nextInt(correctEndings.length)];
      }
      return randomEndings;
   }

   //Note these will crash program, do not use
   public static String[] generateRandomIncorrectPrefixes(int numberOfPrefixes){
      String[] randomPrefixes = new String[numberOfPrefixes];
      String[] incorrectPrefixes = {"http://", "ww.", "httd://www."};
      Random rand = new Random();
      for (int i = 0; i < numberOfPrefixes; i++) {
         randomPrefixes[i] = incorrectPrefixes[rand.nextInt(incorrectPrefixes.length)];
      }
      return randomPrefixes;
   }

   public static String[] generateRandomIncorrectEndings(int numberOfEndings){
      String[] randomEndings = new String[numberOfEndings];
      String[] incorrectEndings = {"", ".", ".com/..", ".com/../"};
      Random rand = new Random();
      for (int i = 0; i < numberOfEndings; i++) {
         randomEndings[i] = incorrectEndings[rand.nextInt(incorrectEndings.length)];
      }
      return randomEndings;
   }
}
