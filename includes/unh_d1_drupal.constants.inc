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

const UNH_D1_DRUPAL_GOOGLE_ET_CODE = "
<pre class='google-track-enrollments-script'>
<script>
var trackOutboundLink = function(url) {
  ga('send', 'event', 'outbound', 'click', removeQueryStringParameter('cspIndex', url), {
    'transport': 'beacon',
    'hitCallback': function(){document.location = url;}
  });
}
</script>
</pre>
";

define("UNH_D1_DRUPAL_GOOGLE_ET_TITLE", "Google Track Enrollments (MISSING REQUIREMENTS - enrollment tracking is disabled)");
const UNH_D1_DRUPAL_GOOGLE_ET_DESC_ADDL = "
<div style='margin-bottom:5px;'>
**THIS FEATURE SHOULD NOT BE ENABLED UNTIL THE FOLLOWING REQUIREMENTS ARE MET**<br>
&nbsp;&nbsp;&nbsp;&nbsp;1) You must be using <a href='https://support.google.com/tagmanager/answer/2574305' target='_blank'>Google Tag Manager</a> to manage your analytics tracking.<br>
&nbsp;&nbsp;&nbsp;&nbsp;2) The 'Google Analytics' module must be enabled and configured with a Google Analytics ID (UA-XXX).<br>
&nbsp;&nbsp;&nbsp;&nbsp;3) The 'Add to Head' module must be enabled and configured with a tracking code snippet as described below.
</div>
<div style='margin-bottom: 5px;'>The tracking code must be an 'Add to Head' module snippet named 'google-track-enrollments' and must be entered modified as below (as described in the <a href='https://support.google.com/analytics/answer/1136920?hl=en' target='_blank'>google tracking code documentation</a>). 
</div>
" . UNH_D1_DRUPAL_GOOGLE_ET_CODE . "
";

define("UNH_D1_DRUPAL_GOOGLE_ET_DESC", "
<div style='margin-bottom: 5px;'>
This feature adds the necessary code for tracking of enrollment button clicks.  This feature requires the 'Google Analytics' and the 'Add to Head' modules to be installed, enabled, and appropriately configured.
</div>
");


/**
 * TIME CONSTANTS.
 */
// define("UNH_D1_DRUPAL_DATE_FORMAT", "d M Y");
define("UNH_D1_DRUPAL_DATE_FORMAT", "M d, Y");
define("UNH_D1_DRUPAL_TIME_FORMAT", "h:ia");
define("UNH_D1_DRUPAL_DATE_TIME_FORMAT", UNH_D1_DRUPAL_DATE_FORMAT . '  ' . UNH_D1_DRUPAL_TIME_FORMAT);



/**
 * RIGHT RAIL SECTION BLOCK LIST SETTINGS CONSTANTS.
 */
define("UNH_D1_DRUPAL_BODY_SECTIONS_SHOW_START_DATE_ONLY", 0);
define("UNH_D1_DRUPAL_BODY_SECTIONS_SHOW_START_AND_END_DATE", 1);
 
define("UNH_D1_DRUPAL_BODY_SECTIONS_SHOW_START_TIME_ONLY", 0);
define("UNH_D1_DRUPAL_BODY_SECTIONS_SHOW_START_AND_END_TIME", 1);

/* RR SORT CONSTANTS - style */
define("UNH_D1_DRUPAL_BODY_SECTIONS_SORT_BY_SECTION_DATE_THEN_TITLE", 0);
define("UNH_D1_DRUPAL_BODY_SECTIONS_SORT_BY_SECTION_TITLE", 1);

/* SORT CONSTANTS - direction */
define("UNH_D1_DRUPAL_SORT_ASCENDING", 0);
define("UNH_D1_DRUPAL_SORT_DESCENDING", 1);

/**
 * CONSTANTS COURSE SEARCH BLOCKS/PAGES
 */

/* COURSE TYPE - from 'Course Types' vocab */
define("UNH_D1_DRUPAL_COURSETYPES_DESTINYONE", "DestinyOne");
define("UNH_D1_DRUPAL_COURSETYPES_NONDESTINYONE", "Non-DestinyOne");

/* COURSE STATUSES - must correspond with the 'course status' taxonomy. */
define("UNH_D1_DRUPAL_NON_D1_COURSE_IS_AVAILABLE", "1");
define("UNH_D1_DRUPAL_NON_D1_COURSE_IS_UNAVAILABLE", "0");

// SECTION STATUSES - must correspond with the 'section status' taxonomy
define("UNH_D1_DRUPAL_NON_D1_SECTION_IS_AVAILABLE", "available");
define("UNH_D1_DRUPAL_NON_D1_SECTION_IS_WAITLISTED", "waitlisted");
define("UNH_D1_DRUPAL_NON_D1_SECTION_WILL_BE_AVAILABLE", "future offering");


// These constants define wording and states for various search bar elements.
define("NO_TITLE", "<none>");
define("UNH_D1_DRUPAL_COURSESEARCHBAR_BLOCKTITLE_DEFAULT", "UNH D1 Course Search Bar Block");
define("UNH_D1_DRUPAL_COURSESEARCHBAR_LABEL_DEFAULT", "What do you want to learn?");
define("UNH_D1_DRUPAL_COURSESEARCHBAR_TAB_DEFAULT", "CHOOSE A TOPIC");
define("UNH_D1_DRUPAL_COURSESEARCHBAR_PHRASE_DEFAULT", "Choose your topics...");
define("UNH_D1_DRUPAL_COURSESEARCHBAR_SUBMIT_DEFAULT", "SEARCH BY TOPICS");
define("UNH_D1_DRUPAL_COURSESEARCHBAR_FILTERS_DEFAULT", TRUE);

define("UNH_D1_DRUPAL_COURSESEARCHBYTEXT_BLOCKTITLE_DEFAULT", "UNH D1 Course Search by Text Block");

define("UNH_D1_DRUPAL_EXCLUDE_NONNODE", TRUE);// These constants determine which courses a course search should exclude:
// Ex: exclude_nonnode means delete results that don't have an equivalent Drupal 'course' node
define("UNH_D1_DRUPAL_EXCLUDE_NONE", 0);
define("UNH_D1_DRUPAL_EXCLUDE_ORPHANS", 1);
define("UNH_D1_DRUPAL_EXCLUDE_NON_ORPHANS", 2);

// DATE FORMAT - how the heck do you get this programmatically from the
// content type definition??
define("UNH_D1_DRUPAL_DATE_FORMAT_MACH_NAME", 'short_date_day_first_no_time');
define("UNH_D1_DRUPAL_TIME_FORMAT_MACH_NAME", 'time');

// CERTIFICATE ICON
//define("UNH_D1_DRUPAL_CERTIFICATE_ICON", 'fa-graduation-cap');
define("UNH_D1_DRUPAL_CERTIFICATE_ICON", 'fa-certificate');





