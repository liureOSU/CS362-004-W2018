import junit.framework.TestCase;

public class InputPartitionTest extends TestCase {

    public InputPartitionTest(String testName) {
        super(testName);
    }

    public void testSchemePartition() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);

        String testString = "www.amazon.com";

        ResultPair[] schemePairs = {new ResultPair("http://", true),
                                    new ResultPair("http:/", false),
                                    new ResultPair("http:", false),
                                    new ResultPair("3://", false),
                                    new ResultPair("://", false)};
                                    //new ResultPair("ftp://", true)};  // BUG: found when using scheme other than http://

        for (int i = 0; i < schemePairs.length; i++) {
            String testUrl = schemePairs[i].item + testString;
            boolean testValid = !schemePairs[i].valid;
            if (testValid == urlVal.isValid(testUrl)) {
                System.out.println("PASS: " + schemePairs[i].item + testString + " is " + testValid);
            }
            else {
                System.out.println("FAIL: " + schemePairs[i].item + testString);
            }
        }
    }

    public void testAuthPartition() {
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
    }

    public void testPathPartition() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS + UrlValidator.ALLOW_LOCAL_URLS);

        String beforeAuth = "http://www.amazon.com";

        ResultPair[] pathPairs = {new ResultPair("/home", true),
                new ResultPair("/home/index", true),
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
    }
}
