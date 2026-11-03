//
//  Terminal.h
//  iSH
//
//  Created by Theodore Dubois on 10/18/17.
//

#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

struct tty;

@interface Terminal : NSObject

+ (Terminal *)terminalWithType:(int)type number:(int)number;
#if !ISH_LINUX
// Returns a strong struct tty and a Terminal that has a weak reference to the same tty
+ (Terminal *)createPseudoTerminal:(struct tty **)tty;
#endif

+ (Terminal *)terminalWithUUID:(NSUUID *)uuid;
@property (readonly) NSUUID *uuid;

+ (void)convertCommand:(NSArray<NSString *> *)command toArgs:(char *)argv limitSize:(size_t)maxSize;

- (int)sendOutput:(const void *)buf length:(int)len;
- (void)sendInput:(NSData *)input;

- (NSString *)arrow:(char)direction;

// Make this terminal no longer be the singleton terminal with its type and number. Will happen eventually if all references go away, but sometimes you want it to happen now.
- (void)destroy;
/// A command (not the shell) owns the terminal's foreground: the tty's
/// foreground process group differs from its session. Keep Screen Awake uses it.
- (BOOL)foregroundCommandRunning;

@property (readonly) WKWebView *webView;
@property (nonatomic, copy) NSString *bootstrapStyleJSON;
@property (nonatomic) BOOL enableVoiceOverAnnounce;
/// YES while the application is on the alternate screen: there is no
/// scrollback to drag, so gestures have to become input instead.
@property (readonly) BOOL alternateScreen;
// Use KVO on this
@property (readonly) BOOL loaded;

@end

extern struct tty_driver ios_console_driver;
