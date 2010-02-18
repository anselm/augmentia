
@interface ASyncImage : UIView {
    NSURLConnection* connection;
    NSMutableData* data;
}
- (void)loadImageFromURL:(NSURL*)url;	
@end
