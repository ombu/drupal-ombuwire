(function ($) {

$(function() {

  if ($('#ombuwire-sidebar:not(.processed)').length == 0) {
    return;
  }

  var $sidebar = $('#ombuwire-sidebar'),
      $cloak = $('.cloak', $sidebar),
      $opener = $('.opener', $sidebar),
      $closer = $('.closer', $sidebar),
      $regionsLabel = $('#ombuwire-regions-label'),
      $regionsCheckbox = $('input', $regionsLabel),
      fullWidth;

  // move the sidebar far off screen so we can measure its full width
  $sidebar.css({left: '-999px'});
  $cloak.css({display: 'block'});
  fullWidth = $sidebar.width();

  // pull the sidebar just off the screen to the left
  $sidebar.css({left: '-'+fullWidth+'px'});

  // open/close click handlers
  function open(e) {
    if (e) { e.preventDefault(); }
    $sidebar.animate({left: '0px'}, {duration: 'fast'});
    $opener.fadeOut('fast');
    $.cookie('ombuwire.open', 1);
  }

  function close(e) {
    if (e) { e.preventDefault(); }
    $sidebar.animate({left: '-'+fullWidth+'px'}, {duration: 'fast'});
    $opener.fadeIn('fast');
    $.cookie('ombuwire.open', 0);
  }


  // bind handlers
  $opener.click((function() {
    return open;
  })());

  $closer.click((function() {
    return close;
  })());


  // Initial state
  if ($.cookie('ombuwire.open') == 1) {
    $sidebar.css({left: '0px'});
    $opener.hide();
  }

  $('a.noclick').click(function(e) {
    e.preventDefault();
    return false;
  });

  function ucwords (str) {
    return (str + '').replace(/^([a-z])|\s+([a-z])/g, function ($1) {
        return $1.toUpperCase();
    });
  }

  function regionsHighlight(e) {
    if (e) { e.preventDefault(); }
    $('body').addClass('ombuwire-region-outlines');
    $.cookie('ombuwire.region-outlines', 1);

    // Only run the first time
    $('.region:not(.ombuwire-processed)').each(function() {
      var $r = $(this);
      if ($r.css('position') == 'static') {
        $r.css('position', 'relative');
      }

      var classes = $r.attr("className").split(" "),
          regionName;
      for (var i = 0; i < classes.length; i++){
        if (classes[i].substr(0, 7) == "region-"){
          regionName = classes[i].substr(7).replace('-', ' ');
          break;
        }
      }
      $r.append('<label class="region-label">' + ucwords(regionName) + '</label>');
      $r.addClass('ombuwire-processed');
    });
  }

  function regionsUnhighlight(e) {
    if (e) { e.preventDefault(); }
    $('body').removeClass('ombuwire-region-outlines');
    $.cookie('ombuwire.region-outlines', 0);
  }

  if ($('.region').length > 0) {
    $regionsLabel.show();
    $regionsCheckbox.change((function() {
      return function(e) {
        if ($(this).is(':checked')) {
          regionsHighlight();
        }
        else {
          regionsUnhighlight();
        }
      }
    })());
    if ($.cookie('ombuwire.region-outlines') == 1) {
      $regionsCheckbox.attr('checked', 'checked');
      regionsHighlight();
    }
  }


  $sidebar.addClass('processed');

});

})(jQuery);