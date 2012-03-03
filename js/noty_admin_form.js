(function($) {
  Drupal.behaviors.noty_messages = {
    attach: function(context) {
    //butt click fxn
    $('#edit-noty-messages-test-noty').click(function(){
      //get name
      var name = $(this).attr('name');
      // get current actives
      if (name == 'global' || $('#edit-noty-messages-global-is-noty-' + name).is(':checked')){
        // change settings
        var notySettings = Drupal.settings.notyMessages;
        console.log($('#edit-noty-messages-' + name + '-type :selected').val());
        console.log($('#edit-noty-messages-' + name + '-layout :selected').val());
        console.log($('#edit-noty-messages-' + name + '-text-align :selected').val());
        console.log($('#edit-noty-messages-' + name + '-speed').val());
        console.log($('#edit-noty-messages-' + name + '-timeout').val());
        console.log($('#edit-noty-messages-' + name + '-closable').is(':checked'));
        console.log($('#edit-noty-messages-' + name + '-click-close').is(':checked'));
        console.log($('#edit-noty-messages-' + name + '-modal').is(':checked'));
        console.log($('#edit-noty-messages-' + name + '-admin-path').is(':checked'));

        notySettings.notyType[name] = $('#edit-noty-messages-' + name + '-type :selected').val();
        notySettings.notyLayout[name] = $('#edit-noty-messages-' + name + '-layout :selected').val();
        notySettings.notyTextAlign[name] = $('#edit-noty-messages-' + name + '-text-align :selected').val();
        notySettings.notySpeed[name] = $('#edit-noty-messages-' + name + '-speed').val();
        notySettings.notyTimeout[name] = $('#edit-noty-messages-' + name + '-timeout').val();
        notySettings.notyClosable[name] = $('#edit-noty-messages-' + name + '-closable').is(':checked');
        notySettings.notyClickClose[name] = $('#edit-noty-messages-' + name + '-click-close').is(':checked');
        notySettings.notyModal[name] = $('#edit-noty-messages-' + name + '-modal').is(':checked');

        noty({
          layout: notySettings.notyLayout[name],
          type: notySettings.notyType[name],
          text:"@noty_text",
          textAlign: notySettings.notyTextAlign[name],
          speed: notySettings.notySpeed[name],
          timeout: notySettings.notyTimeout[name],
          closable: notySettings.notyClosable[name],
          closeOnSelfClick: notySettings.notyClickClose[name],
          modal: notySettings.notyModal[name]
        });
        //notySettings.noty[name] = $('#edit-noty-messages-' + name + '-admin-path').is(':checked');

        console.log(notySettings);
      }
      else{
        alert('This is not a noty message');
      }
      //if (name != 'global' && )
      //for (setting in Drupal.settings.notyMessages){

      //}
      return false;
    });
    }
  }
})(jQuery);