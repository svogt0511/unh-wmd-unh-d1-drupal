(function($) {
  Drupal.behaviors.unh_d1_drupal = {
    attach: function (context, settings) {
      unh_d1_drupal_ajax_load(settings.nid, settings.programArea, settings.courseCode, settings.conf, settings.base_url);
      // console.log('SETTINGS: ' + JSON.stringify(settings));
    }
  };
})(jQuery);


function unh_d1_drupal_ajax_load(nid, programArea, courseCode, conf, base_url) { 
  // console.log('RUNNING THE JAVASCRIPT!!'); 
  if (conf.section_status_cached == "0") {
    // console.log('MAKING THE Call!!'); 
    // console.log('base_url: ' + base_url)
    jQuery(".unh-d1-drupal--d1--course-sections-pane").hide();
    jQuery("#ajax-target").load(base_url + "/unh_d1_drupal/ajax/get_section_status/" + nid + '/' + programArea + '/' + courseCode, conf);
  } else {
      // console.log('NOT NOT NOT - MAKING THE Call!!'); 

      jQuery(".unh-d1-drupal--d1--course-sections-pane").show();
  }
}
