<?php

/**
 * @file
 *
 * Constants.
 *
 * @todo: allow overridemaxresults for searchCourseSection
 */

/**
 * Version Info.
 */
define("UNH_D1_DRUPAL_VERSION_7X00_alpha0", "7.x.00.0.alpha.0");

/**
 * Google Enrollments Tracking Code - settings constants.
 */
 
define("UNH_D1_DRUPAL_GOOGLE_ET_CODE". "
&lt;script&gt;
var trackOutboundLink = function(url) {
  ga('send', 'event', 'outbound', 'click', removeQueryStringParameter('cspIndex', url), {
    'transport': 'beacon',
    'hitCallback': function(){document.location = url;}
  });
}
&lt;/script&gt;
";

define("UNH_D1_DRUPAL_GOOGLE_ET_TITLE", "Google Track Enrollments (MISSING REQUIREMENTS - enrollment tracking is disabled)");
define("UNH_D1_DRUPAL_GOOGLE_ET_DESC_ADDL", "
<div style='margin-bottom:5px;'>
**THIS FEATURE CANNOT BE ENABLED UNTIL THE FOLLOWING REQUIREMENTS ARE MET**<br>
&nbsp;&nbsp;&nbsp;&nbsp;1) Enable the 'Google Analytics' module and configure it with a Google Analytics ID (UA-XXX).<br>
&nbsp;&nbsp;&nbsp;&nbsp;2) Enable the 'Add to Head' module and configure the Google tracking code snippet with the name 'google-track-enrollments'.
</div>
<div style='margin-bottom: 5px;'>The tracking code must in the 'Add to Head' snippet must be named 'google-track-enrollments' and must be entered modified as below from the documented tracking code at: https://support.google.com/analytics/answer/1136920?hl=en
</div>
<pre>
" . UNH_D1_DRUPAL_GOOGLE_ET_CODE . "
</pre>
");

define("UNH_D1_DRUPAL_GOOGLE_ET_DESC", "
<div style='margin-bottom: 5px;'>
Adds the necessary code for tracking of enrollment button clicks.  This feature requires the 'Google Analytics' and the 'Add to Head' modules to be installed, enabled, and appropriately configured.
</div>
");












