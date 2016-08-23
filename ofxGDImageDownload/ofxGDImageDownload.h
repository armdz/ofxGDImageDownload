//
//  ofxGDImageDownload.h
//  googleDocsImage
//
//  Created by lolo on 8/22/16.
//  http://armdz.com
//

#ifndef ofxGDImageDownload_hpp
#define ofxGDImageDownload_hpp

#include <stdio.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include "Poco/Net/AcceptCertificateHandler.h"
#include "Poco/Net/InvalidCertificateHandler.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/HTTPSStreamFactory.h"
#include "ofMain.h"

class ofxGDImageDownload : ofThread
{
    
public:
    ofxGDImageDownload();
    ~ofxGDImageDownload();
    void    setup(string    _key);
    void    download(ofImage    *_image,string _id);
    void    stop();
    void    threadedFunction();
    void    urlResponse(ofHttpResponse & response);
private:
    void    download_image();
    void    dispatch_download_event(ofImage  _image);
    void    dispatch_error_event(string _message);
    
    Poco::Net::Context::Ptr ssl_context;
    Poco::Net::HTTPSClientSession *http_session;
    Poco::Net::HTTPRequest  *http_req;
    Poco::URI uri;

    map<string,string> headers;
    
    string  api_key;
    string  google_docs_base_url;
    string  current_image_id;
    string  image_download_path;
    ofImage *image;
};

//  GDImageDownloadEvent
//  not the best, but less files for a simple addon


class ofxGDImageDownloadEvent : public ofEventArgs {
    
public:
    
    ofImage image;
    bool    ok;
    string  error;
    
    ofxGDImageDownloadEvent() {
        
    }
    static ofEvent <ofxGDImageDownloadEvent> events;
};

//

#endif /* ofxGDImageDownload_hpp */


