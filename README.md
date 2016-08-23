# ofxGDImageDownload
Little openFramework's addon to download images in Google Drive
I make this to make a "quick backend" (for and agenda) that works with Google Sheets, i sync my OF app with the files and data marked in the sheets and visualize it.

# Requeriments

-	You need a Google Drive Api Ke
-	You need to get the "shareable link" of the image. Then copy the id:
	https://drive.google.com/open?id=ID OF THE IMAGE

# Usage

 ofAddListener(ofxGDImageDownloadEvent::events, this, &ofApp::on_gd_event);	//	Register for event
 gd_image_download.setup("YOUR API KEY");	//	setup with your api key
 gd_image_download.download(&image,"IMAGE ID");		//	pointer to and ofImage and Google Drive image id

