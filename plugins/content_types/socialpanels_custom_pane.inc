<?php
$plugin = array(
	'single' => TRUE,  // Just do this one, it is needed.
	'title' => t('Social Panels Pane'),  // Title to show up on the pane screen.
	'description' => t('Twitter and Facebook feeds in a block view.'), // Description to show up on the pane screen.
	'category' => t('Third Party'), // A category to put this under.
	'edit form' => 'socialpanels_pane_custom_pane_edit_form', // A function that will return the settings form for the pane.
	'render callback' => 'socialpanels_pane_custom_pane_render', // A function that will return the renderable content.
	'admin info' => 'socialpanels_pane_custom_pane_admin_info', // A function that will return the information displayed on the admin screen (optional).
	'defaults' => array( // Array of defaults for the settings form.
		'sp_twitterUser' 		=> '',
		'sp_twitterTimeline' 	=> 'true',
		'sp_twitterWidth' 		=> '300',
		'sp_twitterHeight' 		=> '500',
		'sp_twitterLimit' 		=> '20',
		'sp_twitterAdvanced'	=> array(
			'sp_twitterRelated' 	=> '',
			'sp_twitterAria' 		=> 'polite',
			'sp_twitterTheme' 		=> 'light',
			'sp_twitterReplies' 	=> 'false',
			'sp_twitterBorder' 		=> '',
			'sp_twitterLink' 		=> '',
			'sp_twitterChrome' 		=> '',
			'sp_twitterCount' 		=> 'true',
		),  
		'sp_facebookUser' 		=> '',
		'sp_facebookStream' 	=> 'true',
		'sp_facebookWidth' 		=> '300',
		'sp_facebookHeight' 	=> '504',
		'sp_facebookAdvanced'	=> array(
			'sp_facebookFaces'		=> 'true',
			'sp_facebookBorder'		=> 'false',
			'sp_facebookHeader'		=> 'true',
			'sp_facebookTheme' 		=> 'light',
		),
	),
);


/**
 * An edit form for the pane's settings.
 */
function socialpanels_pane_custom_pane_edit_form($form, &$form_state) {
	$conf = $form_state['conf'];
	$form['sp_twitterUser'] = array(
		'#type' => 'textfield',
		'#title' => t('Twitter User'),
    	'#description' => t('User to display information from. If this field is empty, Twitter isn\'t shown.'),
    	'#default_value' => $conf['sp_twitterUser'],
  	);
  	$options = array('button' => t('Hide'), 'timeline' => t('Show'));
  	$form['sp_twitterTimeline'] = array(
    	'#type' => 'radios',
    	'#title' => t('Twitter Timeline'),
		'#default_value' => $conf['sp_twitterTimeline'],
    	'#description' => t('Whether to display or not user timeline.'),
		'#options' => $options,
  	);
	$form['sp_twitterLimit'] = array(
		'#type' => 'textfield',
		'#title' => t('Twitter Limit'),
    	'#description' => t('To fix the size of a timeline to a preset number of Tweets'),
    	'#default_value' => $conf['sp_twitterLimit'],
		'#size' =>4, 
  	);
	$form['sp_twitterWidth'] = array(
		'#type' => 'textfield',
		'#title' => t('Twitter Width'),
    	'#description' => t(''),
    	'#default_value' => $conf['sp_twitterWidth'],
		'#size' =>4, 
  	);
	$form['sp_twitterHeight'] = array(
		'#type' => 'textfield',
		'#title' => t('Twitter Height'),
    	'#description' => t(''),
    	'#default_value' => $conf['sp_twitterHeight'],
		'#size' =>4, 
  	);
  	$form['sp_twitterAdvanced'] = array(
		'#type' => 'fieldset', 
    	'#title' => t('More Twitter options'),  
    	'#collapsible' => TRUE, 
    	'#collapsed' => TRUE, 
    	'#tree' => TRUE,
    );   
		$options = array('false' => t('Hide'), 'true' => t('Show'));
		$form['sp_twitterAdvanced']['sp_twitterCount'] = array(
	    	'#type' => 'radios',
	    	'#title' => t('Twitter followers count'),
	    	'#description' => t('This applies only if you decide not to show your timeline.'),
			'#default_value' => $conf['sp_twitterAdvanced']['sp_twitterCount'],
			'#options' => $options,
	  	);
	  	$form['sp_twitterAdvanced']['sp_twitterRelated'] = array(
	    	'#type' => 'textfield',
	    	'#title' => t('Twitter Related'),
	    	'#description' => t('As per the Tweet and follow buttons, you may provide a comma-separated list of user screen names as suggested followers to a user after they reply, Retweet, or favorite a Tweet in the timeline.'),
	    	'#default_value' => $conf['sp_twitterAdvanced']['sp_twitterRelated'],
	  	);
	  	$options = array('polite' => t('Polite'), 'assertive' => t('Assertive'));
	  	$form['sp_twitterAdvanced']['sp_twitterAria'] = array(
	    	'#type' => 'radios',
	    	'#title' => t('Twitter ARIA'),
	    	'#description' => t('ARIA is an accessibility system that aids people using assistive technology interacting with dynamic web content. <a href="http://www.w3.org/WAI/intro/aria.php" target="_blank">Read more about ARIA on W3C\'s website</a>. By default, the embedded timeline uses the least obtrusive <i>Polite</i>. If you\'re using an embedded timeline as a primary source of content on your page, you may wish to override this to the <i>Assertive</i> setting'),
			'#default_value' => $conf['sp_twitterAdvanced']['sp_twitterAria'],
			'#options' => $options,
	  	);
	  	$options = array('light' => t('Light'), 'dark' => t('Dark'));
	  	$form['sp_twitterAdvanced']['sp_twitterTheme'] = array(
	    	'#type' => 'radios',
	    	'#title' => t('Twitter Theme'),
	    	'#default_value' => $conf['sp_twitterAdvanced']['sp_twitterTheme'],
			'#options' => $options,
	  	);
	  	$options = array('false' => t('Hide'), 'true' => t('Show'));
	  	$form['sp_twitterAdvanced']['sp_twitterReplies'] = array(
	    	'#type' => 'radios',
	    	'#title' => t('Twitter Replies'),
			'#default_value' => $conf['sp_twitterAdvanced']['sp_twitterReplies'],
	    	'#description' => t('Whether to display or not replies. Default is to hide them.'),
			'#options' => $options,
	  	);
	  	$form['sp_twitterAdvanced']['sp_twitterBorder'] = array(
	    	'#type' => 'textfield',
	    	'#title' => t('Twitter border color'),
	    	'#description' => t('Change the border color used by the widget. Takes an #abc123 hex format color.'),
	    	'#default_value' => $conf['sp_twitterAdvanced']['sp_twitterBorder'],
	  	);
	  	$form['sp_twitterAdvanced']['sp_twitterLink'] = array(
	    	'#type' => 'textfield',
	    	'#title' => t('Twitter link color'),
	    	'#description' => t('Note that some icons in the widget will also appear this color.'),
	    	'#default_value' => $conf['sp_twitterAdvanced']['sp_twitterLink'],
	  	);  
	  	$form['sp_twitterAdvanced']['sp_twitterChrome'] = array(
	    	'#type' => 'checkboxes',
	    	'#options' => drupal_map_assoc(array(
				'noheader', 
				'nofooter', 
				'noborders',
				'noscrollbar',
				'transparent'
			)),
	    	'#title' => t('Chrome'),
			'#default_value' => $conf['sp_twitterAdvanced']['sp_twitterChrome'],
			'#description' => t('Check <a href="https://dev.twitter.com/docs/embedded-timelines#timeline-selection" target="_blank">this page</a> to see what each one does.')
	  	);
	$form['sp_facebookUser'] = array(
    	'#type' => 'textfield',
    	'#title' => t('Facebook User'),
    	'#description' => t('User to display information from.'),
    	'#default_value' => $conf['sp_facebookUser'],
  	);
	$options = array('false' => t('Hide'), 'true' => t('Show'));
	$form['sp_facebookStream'] = array(
		'#type' => 'radios',
		'#title' => t('Facebook stream'),
		'#description' => t('Specifies whether to display a stream of the latest posts from the Page\'s wall.'),
		'#default_value' => $conf['sp_facebookStream'],
		'#options' => $options,
	);
	$form['sp_facebookHeight'] = array(
		'#type' => 'textfield',
		'#title' => t('Facebook Height'),
    	'#description' => t(''),
    	'#default_value' => $conf['sp_facebookHeight'],
		'#size' =>4, 
  	);
	$form['sp_facebookWidth'] = array(
		'#type' => 'textfield',
		'#title' => t('Facebook Width'),
    	'#description' => t(''),
    	'#default_value' => $conf['sp_facebookWidth'],
		'#size' =>4, 
  	);
	$form['sp_facebookAdvanced'] = array(
		'#type' => 'fieldset', 
		'#title' => t('More Facebook options'),  
		'#collapsible' => TRUE, 
		'#collapsed' => TRUE, 
		'#tree' => TRUE,
    ); 
		$options = array('false' => t('Hide'), 'true' => t('Show'));
		$form['sp_facebookAdvanced']['sp_facebookFaces'] = array(
    		'#type' => 'radios',
			'#title' => t('Facebook show faces'),
			'#description' => t('Specifies whether or not to display profile photos in the plugin.'),
			'#default_value' => $conf['sp_facebookAdvanced']['sp_facebookFaces'],
			'#options' => $options,
		);
		$options = array('false' => t('Hide'), 'true' => t('Show'));
		$form['sp_facebookAdvanced']['sp_facebookBorder'] = array(
    		'#type' => 'radios',
			'#title' => t('Facebook show border'),
			'#description' => t('Specifies whether or not to show a border around the plugin.'),
			'#default_value' => $conf['sp_facebookAdvanced']['sp_facebookBorder'],
			'#options' => $options,
		);
		$options = array('false' => t('Hide'), 'true' => t('Show'));
		$form['sp_facebookAdvanced']['sp_facebookHeader'] = array(
    		'#type' => 'radios',
			'#title' => t('Facebook header'),
			'#description' => t('Specifies whether to display the Facebook header at the top of the plugin.'),
			'#default_value' => $conf['sp_facebookAdvanced']['sp_facebookHeader'],
			'#options' => $options,
		);
	  	$options = array('light' => t('Light'), 'dark' => t('Dark'));
	  	$form['sp_facebookAdvanced']['sp_facebookTheme'] = array(
	    	'#type' => 'radios',
	    	'#title' => t('Facebook Theme'),
	    	'#default_value' => $conf['sp_facebookAdvanced']['sp_facebookTheme'],
			'#options' => $options,
	  	);
	return $form;
}
 
/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 * Notice, the magic that automatically does that for you.
 */
function socialpanels_pane_custom_pane_edit_form_submit(&$form, &$form_state) {
	foreach (array_keys($form_state['plugin']['defaults']) as $key) {
		if (isset($form_state['values'][$key])) {
			$form_state['conf'][$key] = $form_state['values'][$key];
		}
	}
} 

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function socialpanels_pane_custom_pane_render($subtype, $conf, $panel_args, $context = NULL) {
	$block = new stdClass();
	$html = '
				<div class="circle dark clearfix discusion-white">
					<span>
						<em></em>
						</span>
					<h3>
						<a href="#"></a>
						<a title="Redes Sociales" href="">Redes Sociales</a>
					</h3>
				</div>	
	';
	$id_twitter=variable_get('sp_twitterWidgetId');
	if(isset($id_twitter) && !empty($conf['sp_twitterUser'])){
		$twitter_follow = '
			<div class="sb-twitter follow"><a href="https://twitter.com/'.$conf['sp_twitterUser'].'"
				class="twitter-follow-button" 
				data-show-count="'.$conf['sp_twitterAdvanced']['sp_twitterCount'].'" 
				data-size="large">Seguir a @'.$conf['sp_twitterUser'].'</a><script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?"http":"https";if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+"://platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document, "script", "twitter-wjs");</script></div>
				';
		$chrome = array();
		foreach($conf['sp_twitterAdvanced']['sp_twitterChrome'] as $k => $v) {
			if($v!==0) { array_push($chrome,$k); }
		}
		$twitter_timeline = '
			<div class="sb-twitter timeline">
				<a class="twitter-timeline" 
					href="https://twitter/'.$conf['sp_twitterUser'].'" 
					data-screen-name="'.$conf['sp_twitterUser'].'" 
					data-show-replies="'.$conf['sp_twitterAdvanced']['sp_twitterReplies'].'" 
					data-widget-id="'.variable_get('sp_twitterWidgetId').'" 
					data-theme="'.$conf['sp_twitterAdvanced']['sp_twitterTheme'].'" 
					data-related="'.$conf['sp_twitterAdvanced']['sp_twitterRelated'].'" 
					data-border-color="'.$conf['sp_twitterAdvanced']['sp_twitterBorder'].'" 
					data-link-color="'.$conf['sp_twitterAdvanced']['sp_twitterLink'].'" 
					data-tweet-limit="'.$conf['sp_twitterLimit'].'" 
					data-chrome="'.implode(' ',$chrome).'" 
					width="'.$conf['sp_twitterWidth'].'" 
					height="'.$conf['sp_twitterHeight'].'" 
					data-aria-polite="'.$conf['sp_twitterAdvanced']['sp_twitterAria'].'">
				</a>
			</div>
			<script type="text/javascript">
				!function(d,s,id){
					var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?"http":"https";
					if(!d.getElementById(id)){
						js=d.createElement(s);
						js.id=id;js.src=p+"://platform.twitter.com/widgets.js";
						fjs.parentNode.insertBefore(js,fjs);
					}
				}(document,"script","twitter-wjs");
				
				jQuery(document).ready(function() {
					jQuery("iframe").contents().find(".inline-media").css("display","none");
					jQuery("iframe").contents().find(".customisable-border").css("border","0px");
					jQuery("iframe").contents().find(".timeline-footer").css("background","#fff");
				});								
			</script>
			
						
			';
		$html .= ($conf['sp_twitterTimeline']=='timeline') ? $twitter_timeline : $twitter_follow;
	}

	if(variable_get('sp_fbappId')!=='') {
		$facebook_timeline = '
			<div class="sb-facebook timeline"><div class="fb-like-box"
				data-href="https://www.facebook.com/'.$conf['sp_facebookUser'].'"
				data-colorscheme="'.$conf['sp_facebookAdvanced']['sp_facebookTheme'].'"
				data-show-faces="'.$conf['sp_facebookAdvanced']['sp_facebookFaces'].'"
				data-stream="'.$conf['sp_facebookStream'].'"
				data-show-border="'.$conf['sp_facebookAdvanced']['sp_facebookBorder'].'"
				data-width="'.$conf['sp_facebookWidth'].'" 
				data-height="'.$conf['sp_facebookHeight'].'" 
				data-header="'.$conf['sp_facebookAdvanced']['sp_facebookHeader'].'"></div>
				<div id="fb-root"></div></div>
				<script type="text/javascript">(function(d, s, id) {
				  var js, fjs = d.getElementsByTagName(s)[0];
				  if (d.getElementById(id)) return;
				  js = d.createElement(s); js.id = id;
				  js.src = "//connect.facebook.net/en_US/all.js#xfbml=1&appId='.variable_get('sp_fbappId').'";
				  fjs.parentNode.insertBefore(js, fjs);
				}(document, "script", "facebook-jssdk"));</script>';		
		$html .= $facebook_timeline;
	}
  
  // initial content is blank
  $block->title = t('Social Networks'); // This will be overridden by the user within the panel options.  
  $block->content = $html;
 
  return $block;
}


/**
 * 'admin info' callback for panel pane.
 */
function socialpanels_pane_custom_pane_admin_info($subtype, $conf, $contexts) {
	if (!empty($conf)) {
		$block = new stdClass;
		$block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
		$block->content = 'Twitter user: '.$conf['sp_twitterUser'].'<br />'.'Facebook User: '.$conf['sp_facebookUser'];
		return $block;
	}
}