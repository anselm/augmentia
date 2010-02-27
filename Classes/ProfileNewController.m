
#import "ProfileNewController.h"
#import "AppDelegate.h"
#import "db.h"

@implementation ProfileNewController

- (id) init {
	self = [ super initWithStyle: UITableViewStyleGrouped ];
	if (self != nil) {
		self.title = @"Settings";
	}
	return self;
}

- (void) loadView {
	[ super loadView ];
}

-(void) connectToTwitter:(UIButton*)sender {
	NSLog(@"button pressed");
	AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	[d setActiveViewController:@"TwitterAuth"];
}

-(void) saveAction:(id) sender {

	// - connect to twitter right now and validate this account

	if( FALSE ) {
		// Advise of problem		
		NSString *str = [[NSString alloc] initWithFormat:playerNameField.text];
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Difficulty validating account!" 
														message:str delegate:self 
											  cancelButtonTitle:@"Dismiss" 
											  otherButtonTitles:nil];
		[alert show];
		[str release];
		[alert release];
	} else {
		// Save the account
		AppDelegate *d = (AppDelegate *)[[UIApplication sharedApplication] delegate];
		[d.db addProfile:playerNameField.text Password:playerPasswordField.text];
		[d setActiveViewController:@"profiles_from_profile_new"];
	}
}

-(void) textFieldDoneEditing : (id) sender {
	//name = @"sss";
	//password = @"aaaa";
	[sender resignFirstResponder];
}

- (void)viewDidLoad {
	[super viewDidLoad];
	UIBarButtonItem *addButton = [[UIBarButtonItem alloc]
                                  initWithBarButtonSystemItem:UIBarButtonSystemItemSave target:self action:@selector(saveAction:)];
	self.navigationItem.rightBarButtonItem = addButton;
}	


- (BOOL)shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation)interfaceOrientation {
	return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)didReceiveMemoryWarning {
	[ super didReceiveMemoryWarning ];
}

- (void)dealloc {
	[ super dealloc ];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return 3;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    switch (section) {
		case(0):
			return 3;
			break;
		case(1):
			return 6;
			break;
		case(2):
			return 1;
			break;
    }
	
    return 0;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    switch (section) {
		case(0):
			return @"Profile Settings";
			break;
		case(1):
			return @"Game Settings";
			break;
		case(2):
			return @"About";
			break;
    }
    return nil;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *CellIdentifier = [ NSString stringWithFormat: @"%d:%d", [ indexPath indexAtPosition: 0 ], [ indexPath indexAtPosition:1 ]];
	
    UITableViewCell *cell = [ tableView dequeueReusableCellWithIdentifier: CellIdentifier];
	
    if (cell == nil) {
		cell = [ [ [ UITableViewCell alloc ] initWithFrame: CGRectZero reuseIdentifier: CellIdentifier] autorelease ];
		
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
		
		switch ([ indexPath indexAtPosition: 0]) {
			case(0):
				switch ([ indexPath indexAtPosition: 1 ]) {
					case(0):
					{
						playerNameField = [ [ UITextField alloc ] initWithFrame: CGRectMake(120, 12, 145, 28) ];
						playerNameField.adjustsFontSizeToFitWidth = YES;
						playerNameField.textColor = [UIColor blackColor];
						playerNameField.font = [UIFont systemFontOfSize:18.0];
						playerNameField.placeholder = @"";
						//playerNameField.backgroundColor = [UIColor whiteColor];
						//playerNameField.borderStyle = UITextBorderStyleLine;
						playerNameField.autocorrectionType = UITextAutocorrectionTypeNo; // no auto correction support
						playerNameField.autocapitalizationType = UITextAutocapitalizationTypeNone; // no auto capitalization support
						playerNameField.textAlignment = UITextAlignmentLeft;
						playerNameField.keyboardType = UIKeyboardTypeDefault; // use the default type input method (entire keyboard)
						playerNameField.returnKeyType = UIReturnKeyDone;
						playerNameField.tag = 0;
						playerNameField.delegate = self;
						playerNameField.secureTextEntry = false;
						playerNameField.clearButtonMode = UITextFieldViewModeNever; // no clear 'x' button to the right
						playerNameField.text = @"";
						[ playerNameField setEnabled: YES ];
						[ cell addSubview: playerNameField ];
						//cell.text = @"Player";
						[cell.textLabel setText:@"Player"];
						[playerNameField release];
						[playerNameField becomeFirstResponder];
						break;
					}
					case(1):
					{
						playerPasswordField = [ [ UITextField alloc ] initWithFrame: CGRectMake(120, 12, 145, 28) ];
						playerPasswordField.adjustsFontSizeToFitWidth = YES;
						playerPasswordField.textColor = [UIColor blackColor];
						playerPasswordField.font = [UIFont systemFontOfSize:18.0];
						playerPasswordField.placeholder = @"";
						//playerPasswordField.backgroundColor = [UIColor whiteColor];
						//playerPasswordField.borderStyle = UITextBorderStyleLine;
						playerPasswordField.autocorrectionType = UITextAutocorrectionTypeNo; // no auto correction support
						playerPasswordField.autocapitalizationType = UITextAutocapitalizationTypeNone; // no auto capitalization support
						playerPasswordField.adjustsFontSizeToFitWidth = YES;
						playerPasswordField.keyboardType = UIKeyboardTypeDefault; // use the default type input method (entire keyboard)
						playerPasswordField.returnKeyType = UIReturnKeyDone;
						playerPasswordField.tag = 0;
						playerPasswordField.delegate = self;
						playerPasswordField.secureTextEntry = true;
						playerPasswordField.clearButtonMode = UITextFieldViewModeNever; // no clear 'x' button to the right
						playerPasswordField.text = @"";
						[ playerPasswordField setEnabled: YES ];
						[ cell addSubview: playerPasswordField ];
						//cell.text = @"Player";
						[cell.textLabel setText:@"Password"];
						[playerPasswordField release];
						//[playerPasswordField becomeFirstResponder];
						break;
					}
					case(2):
					{
						// http://developer.apple.com/iphone/library/documentation/UserExperience/Conceptual/TableView_iPhone/TableViewCells/TableViewCells.html

						UIButton *button = [[UIButton buttonWithType:UIButtonTypeRoundedRect] retain];
						button.frame = CGRectMake(60, 6, 200, 35);
						//[button setFrame: CGRectMake(120,10,100,10)];
						//button.backgroundColor = [UIColor blueColor];
						[button setTitle:@"Connect to Twitter" forState:UIControlStateNormal];
						[button addTarget:self action:@selector(connectToTwitter:) forControlEvents:UIControlEventTouchUpInside];

						//button.center = self.center;
						//[cell.textLabel setText:@"Role"];

						//[button setCenter:CGPointMake(120, 10)];

					//	[button setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
					//	[button setTitleColor:[UIColor blackColor] forState:UIControlEventTouchDown];
					//	button.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
					//	button.contentHorizontalAlignment = UIControlContentHorizontalAlignmentCenter;						

						UIView *transparentBackground = [[UIView alloc] initWithFrame:CGRectZero];
						transparentBackground.backgroundColor = [UIColor clearColor];
						cell.backgroundView = transparentBackground;
						//cell.contentView.backgroundColor = [UIColor blueColor];
						
						[cell addSubview:button ];
						[button release];
						break;
					}
				}
				break;

			case(1):
				switch([ indexPath indexAtPosition: 1]) {
					case(0):
					{
						UISlider *musicVolumeControl = [ [ UISlider alloc ] initWithFrame: CGRectMake(170, 0, 125, 50) ];
						musicVolumeControl.minimumValue = 0.0;
						musicVolumeControl.maximumValue = 10.0;
						musicVolumeControl.tag = 0;
						musicVolumeControl.value = 3.5;
						musicVolumeControl.continuous = YES;
						[musicVolumeControl addTarget:self action:@selector(sliderAction:) forControlEvents:UIControlEventValueChanged];
						[ cell addSubview: musicVolumeControl ];
						//cell.text = @"Music Volume";
						[cell.textLabel setText:@"Music Volume"];
						[ musicVolumeControl release ];
						break;
					}
					case(1):
					{
						UISlider *gameVolumeControl = [ [ UISlider alloc ] initWithFrame: CGRectMake(170, 0, 125, 50) ];
						gameVolumeControl.minimumValue = 0.0;
						gameVolumeControl.maximumValue = 10.0;
						gameVolumeControl.tag = 1;
						gameVolumeControl.value = 3.5;
						gameVolumeControl.continuous = YES;
						[gameVolumeControl addTarget:self action:@selector(sliderAction:) forControlEvents:UIControlEventValueChanged];
						[ cell addSubview: gameVolumeControl ];
						//cell.text = @"Game Volume";
						[cell.textLabel setText:@"Game Volume"];
						[ gameVolumeControl release ];
						break;
					}
					case(2):
					{
						UISegmentedControl *difficultyControl = [ [ UISegmentedControl alloc ] initWithFrame: CGRectMake(170, 5, 125, 35) ];
						[ difficultyControl insertSegmentWithTitle: @"Easy" atIndex: 0 animated: NO ];
						[ difficultyControl insertSegmentWithTitle: @"Hard" atIndex: 1 animated: NO ];
						difficultyControl.selectedSegmentIndex = 0;
						difficultyControl.tag = 2;
						[difficultyControl addTarget:self action:@selector(segmentAction:) forControlEvents:UIControlEventValueChanged];
						[ cell addSubview: difficultyControl ];
						//cell.text = @"Difficulty";
						[cell.textLabel setText:@"Difficulty"];
						[difficultyControl release];
						break;
					}
					case(3):
					{
						UISegmentedControl *actionControl = [[UISegmentedControl alloc] initWithItems:[NSArray arrayWithObjects: @"Leader", @"Player", @"Watcher", nil]];
						actionControl.frame = CGRectMake(145, 5, 150, 35);
						actionControl.selectedSegmentIndex = 1;
						actionControl.tag = 3;
						[actionControl addTarget:self action:@selector(segmentAction:) forControlEvents:UIControlEventValueChanged];
						actionControl.segmentedControlStyle = UISegmentedControlStyleBar;
						
						[cell addSubview:actionControl];
						//cell.text = @"Actions";
						[cell.textLabel setText:@"Role"];
						[actionControl release];
						break;
					}
					case(4):
					{
						UISwitch *resetControl = [ [ UISwitch alloc ] initWithFrame: CGRectMake(200, 10, 0, 0) ];
						resetControl.on = YES;
						resetControl.tag = 1;
						[resetControl addTarget:self action:@selector(switchAction:) forControlEvents:UIControlEventValueChanged];
						[ cell addSubview: resetControl ];
						//cell.text = @"Reset";
						[cell.textLabel setText:@"Reset"];
						[resetControl release];
						break;
					}
					case(5):
					{
						UISwitch *debugControl = [ [ UISwitch alloc ] initWithFrame: CGRectMake(200, 10, 0, 0) ];
						debugControl.on = NO;
						debugControl.tag = 2;
						[debugControl addTarget:self action:@selector(switchAction:) forControlEvents:UIControlEventValueChanged];
						[ cell addSubview: debugControl ];
						//cell.text = @"Debug";
						[cell.textLabel setText:@"Debug"];
						[debugControl release];
						break;
					}						
				}
				break;
				
			case(2):
			{
				UITextField *versionControl = [ [ UITextField alloc ] initWithFrame: CGRectMake(170, 10, 125, 38) ];
				versionControl.text = @"02/28/2010-03:15:23";
				[ cell addSubview: versionControl ];

				[ versionControl setEnabled: YES ];
				versionControl.tag = 2;
				versionControl.delegate = self;
				//cell.text = @"Version";
				[cell.textLabel setText:@"Version"];
				[versionControl release];
				break;
			}
		}
    }
	
    return cell;
}

- (void)segmentAction:(UISegmentedControl*)sender {
    if ([activeTextField canResignFirstResponder])
		[activeTextField resignFirstResponder];
	
    NSLog(@"segmentAction: sender = %d, segment = %d", [sender tag], [sender selectedSegmentIndex]);
}

- (void)sliderAction:(UISlider*)sender {
    if ([activeTextField canResignFirstResponder])
		[activeTextField resignFirstResponder];
	NSLog(@"sliderAction: sender = %d, value = %.1f", [sender tag], [sender value]);
}

- (void)switchAction:(UISwitch*)sender {
    if ([activeTextField canResignFirstResponder])
		[activeTextField resignFirstResponder];
    NSLog(@"switchAction: sender = %d, isOn %d", [sender tag], [sender isOn]);
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField {
    activeTextField = textField;
    NSLog(@"textFieldShouldBeginEditing: sender = %d, %@", [textField tag], [textField text]);
    return YES;
}

- (void)textFieldDidEndEditing:(UITextField *)textField {
    NSLog(@"textFieldDidEndEditing: sender = %d, %@", [textField tag], [textField text]);
	// test scrap
	//AppDelegate *app = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	//[app showGlobe];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    NSLog(@"textFieldShouldReturn: sender = %d, %@", [textField tag], [textField text]);
    activeTextField = nil;
    [textField resignFirstResponder];
    return YES;
}


@end
