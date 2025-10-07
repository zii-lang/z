#include <Z/IO.hpp>
#include <gtest/gtest.h>
#include <ios>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace Z::IO;

TEST(ForwardFileSource, PipeReadTest) {
  int fds[2];
  ASSERT_EQ(pipe(fds), 0); // create pipe

  const char *testData = "hello";
  write(fds[1], testData, 5);
  close(fds[1]); // close write end so EOF is seen

  // Read the pipe into a buffer
  std::vector<char> buffer(5);
  ssize_t n = read(fds[0], buffer.data(), buffer.size());
  ASSERT_EQ(n, 5);
  close(fds[0]); // close read end

  // Wrap buffer in istringstream
  std::string data(buffer.begin(), buffer.end());
  std::istringstream ss(data);

  ForwardFileSource source(ss);

  // Read all bytes
  std::vector<uint8_t> result;
  while (!source.eof()) {
    result.push_back(source.get());
  }

  ASSERT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], 'h');
  EXPECT_EQ(result[1], 'e');
  EXPECT_EQ(result[2], 'l');
  EXPECT_EQ(result[3], 'l');
  EXPECT_EQ(result[4], 'o');
}

TEST(ForwardFileSource, PipePeekTest) {
  int fds[2];
  ASSERT_EQ(pipe(fds), 0); // create pipe

  const char *testData = "hello";
  write(fds[1], testData, 5);
  close(fds[1]); // close write end so EOF is seen

  // Read the pipe into a buffer
  std::vector<char> buffer(5);
  ssize_t n = read(fds[0], buffer.data(), buffer.size());
  ASSERT_EQ(n, 5);
  close(fds[0]); // close read end

  // Wrap buffer in istringstream
  std::string data(buffer.begin(), buffer.end());
  std::istringstream ss(data);

  ForwardFileSource source(ss);

  // --- Test peek ---
  EXPECT_EQ(source.peek(0), 'h'); // peek at current
  EXPECT_EQ(source.peek(1), 'e'); // peek one ahead
  EXPECT_EQ(source.peek(2), 'l'); // peek two ahead

  // --- Test get and ensure cursor advances ---
  EXPECT_EQ(source.get(), 'h');
  EXPECT_EQ(source.pos(), 1);

  EXPECT_EQ(source.peek(0), 'e'); // peek now at new cursor
  EXPECT_EQ(source.get(), 'e');
  EXPECT_EQ(source.get(), 'l');
  EXPECT_EQ(source.get(), 'l');
  EXPECT_EQ(source.get(), 'o');
  EXPECT_TRUE(source.eof());
}

TEST(ForwardFileSource, EmptyInput) {
  std::istringstream ss("");
  ForwardFileSource source(ss);

  EXPECT_TRUE(source.eof());
  EXPECT_THROW(source.get(), std::runtime_error);
  EXPECT_THROW(source.peek(), std::runtime_error);
}

TEST(ForwardFileSource, InvalidStream) {
  std::istringstream ss;
  ss.setstate(std::ios::badbit); // simulate a bad stream

  EXPECT_THROW(ForwardFileSource source(ss), std::runtime_error);
}

class ForwardFileSourceStream : public ::testing::Test {
protected:
  const char *testFileName1 = "test_stream1.txt";
  const char *testFileName2 = "test_stream2.txt";

  void SetUp() override {
    // Create an empty file
    std::ofstream out(testFileName1, std::ios::out);
    std::ofstream out2(testFileName2, std::ios::out);
    out.close();
    out2.close();
  }

  void TearDown() override {
    // Remove the temporary file
    std::remove(testFileName1);
    std::remove(testFileName2);
  }
};

TEST(ForwardFileSourceStream, DetectsMoreDataAfterAppend) {
  const std::string filename = "test_stream1.txt";

  // Step 1: Create and write initial data
  {
    std::ofstream out(filename, std::ios::out);
    out << "abc";
  }

  // Step 2: Open ForwardFileSource for reading
  ForwardFileSource source(filename);

  // Read initial content
  EXPECT_EQ(source.get(), 'a');
  EXPECT_EQ(source.get(), 'b');
  EXPECT_EQ(source.get(), 'c');

  // Should be at EOF after initial read
  EXPECT_TRUE(source.eof());

  // Step 3: Append more data to the same file
  {
    std::ofstream out(filename, std::ios::app);
    out << "xyz";
    out.close();
  }

  // Give filesystem a moment to flush/acknowledge the new data
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Step 4: Try to read more data after append
  // Move the stream position back to ensure it continues
  EXPECT_FALSE(source.eof());

  EXPECT_EQ(source.get(), 'x');
  EXPECT_EQ(source.get(), 'y');
  EXPECT_EQ(source.get(), 'z');
  EXPECT_TRUE(source.eof());
}

TEST(ForwardFileSourceStream, DetectsMoreDataAfterAppend2) {
  const std::string filename = "test_stream2.txt";

  {
    std::ofstream out(filename, std::ios::out);
    out << "abc";
  }

  ForwardFileSource source(filename);

  // Read initial content
  EXPECT_EQ(source.get(), 'a');
  EXPECT_EQ(source.get(), 'b');

  {
    std::ofstream out(filename, std::ios::app);
    out << "xyz";
    out.close();
  }

  // Give filesystem a moment to flush/acknowledge the new data
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Step 4: Try to read more data after append
  // Move the stream position back to ensure it continues
  EXPECT_FALSE(source.eof());

  EXPECT_EQ(source.get(), 'c');
  EXPECT_EQ(source.get(), 'x');
  EXPECT_EQ(source.get(), 'y');
  EXPECT_EQ(source.get(), 'z');
  EXPECT_TRUE(source.eof());
}

TEST(ForwardFileSource, PipeSimulationTest) {
  int fds[2];
  ASSERT_EQ(pipe(fds), 0);

  // Write to pipe
  const char *data = "Hello";
  write(fds[1], data, 5);
  close(fds[1]); // signal EOF

  // Read from pipe into buffer
  std::vector<char> buffer(5);
  read(fds[0], buffer.data(), buffer.size());
  close(fds[0]);

  // Wrap in stringstream
  std::string str(buffer.begin(), buffer.end());
  std::stringstream ss(str);

  ForwardFileSource source(ss);

  // Check content
  EXPECT_EQ(source.get(), 'H');
  EXPECT_EQ(source.get(), 'e');
  EXPECT_EQ(source.get(), 'l');
  EXPECT_EQ(source.get(), 'l');
  EXPECT_EQ(source.get(), 'o');
  EXPECT_TRUE(source.eof());
}
