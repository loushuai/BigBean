/*
 * OpenslSink.h
 *
 * Created on: 2016��5��15��
 *     Author: loushuai
 */

#ifndef JNI_MEDIASINK_AUDIOSINK_OPENSL_OPENSLSINK_H_
#define JNI_MEDIASINK_AUDIOSINK_OPENSL_OPENSLSINK_H_

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "../audiosink.hpp"

namespace bigbean
{

class OpenslSink : public AudioSink
{
public:
  OpenslSink();
  virtual ~OpenslSink();

  int open( uint32_t sampleRate, int channelCount,
            pcm_format_t format=PCM_FORMAT_FIXED_8,
            AudioCallback cb = NULL);

  int start();

private:
	/**
	 *  @brief ����opensl����
	 */
	int CreateEngine();

	/**
	 *  @brief ����audio player
	 */
	int createBufferQueueAudioPlayer(uint32_t sampleRate,
									 int channelCount,
									 pcm_format_t format);

	/**
	  * @brief  ��Ƶ���Żص�����
	  * @author  
	  * @param[in]	bq BufferQueue����ӿ�
	  * @param[in] context �ص���������ݣ�PCM����
	  * @return void
	*/
	static void AudioPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context);	

  	/**
	  * @brief  ��Ƶ�����������
	*/
	SLObjectItf mEngineObject;
	/**
	  * @brief  ��Ƶ��������ӿ�
	*/
	SLEngineItf mEngine;
	/**
	  * @brief  ��Ƶ������������
	*/
	SLObjectItf mOutputMixObject;
	/**
	  * @brief  ��Ƶ���Ŷ���
	*/
	SLObjectItf mPlayerObject;
	/**
	  * @brief  ��Ƶ���Žӿ�
	*/
	SLPlayItf mPlayerPlay;
	/**
	  * @brief  BufferQueue����ӿ�
	*/
	SLAndroidSimpleBufferQueueItf mPlayerBufferQueue;
	/*
	 * @brief �����ӿ�
	 */
	SLVolumeItf mPlayerVolume;

	/*
	 *  @brief �������ص�
	 */
	AudioCallback mCallBack;

	/*
	 * 
	 */
	void *mBuffer;

	/*
	 * 
	 */
	size_t mBufferSize;
};
  
}

#endif /*JNI_MEDIASINK_AUDIOSINK_OPENSL_OPENSLSINK_H_*/
