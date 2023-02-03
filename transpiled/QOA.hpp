// Generated automatically with "cito". Do not edit.
#pragma once
#include <array>
#include <cstdint>
class LMS;
class QOADecoder;

/**
 * Least Mean Squares Filter.
 */
class LMS
{
public:
	LMS() = default;
public:
	void init(int i, int h, int w);
	int predict() const;
	void update(int sample, int residual);
private:
	std::array<int, 4> history;
	std::array<int, 4> weights;
};

/**
 * Decoder of the "Quite OK Audio" format.
 */
class QOADecoder
{
public:
	virtual ~QOADecoder() = default;
	/**
	 * Reads the file header.
	 * Returns <code>true</code> if the header is valid.
	 */
	bool readHeader();
	/**
	 * Returns the file length in samples per channel.
	 */
	int getTotalSamples() const;
	/**
	 * Maximum number of channels supported by the format.
	 */
	static constexpr int maxChannels = 8;
	/**
	 * Returns the number of audio channels.
	 */
	int getChannels() const;
	/**
	 * Returns the sample rate in Hz.
	 */
	int getSampleRate() const;
	/**
	 * Number of samples per frame.
	 */
	static constexpr int frameSamples = 5120;
	/**
	 * Reads and decodes a frame.
	 * Returns the number of samples per channel.
	 * @param output PCM samples.
	 */
	int readFrame(int16_t * output);
	/**
	 * Returns <code>true</code> if all frames have been read.
	 */
	bool isEnd() const;
protected:
	/**
	 * Constructs the decoder.
	 * The decoder can be used for several files, one after another.
	 */
	QOADecoder();
	/**
	 * Reads a byte from the stream.
	 * Returns the unsigned byte value or -1 on EOF.
	 */
	virtual int readByte() = 0;
private:
	int buffer;
	int bufferBits;
	int readBits(int bits);
	int totalSamples;
	int expectedFrameHeader;
	int positionSamples;
	static constexpr int sliceSamples = 20;
	static constexpr int frameSlices = 256;
	int getFrameBytes() const;
	static int clamp(int value, int min, int max);
};
