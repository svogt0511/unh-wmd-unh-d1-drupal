(function($) {
  Drupal.behaviors.unh_d1_drupal = {
    attach: function (context, settings) {
      unh_d1_drupal_ajax_load(settings.courseId, settings.sectionIds, settings.section_status)
    }
  };
})(jQuery);


function unh_d1_drupal_ajax_load(courseId, sectionIds, section_status) {  
  sectionIds.forEach((sectionId) => {
    jQuery("#ajax-target").load("/unh_d1_drupal/ajax/get_section_status/" + courseId + '/' + sectionId);
  });
  
}
