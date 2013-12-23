
    function imagesUpdate(feature){
        setLoadingImage(20);
        loadAndChangeImages(feature);
    }
     function setLoadingImage(count){
        clearImages();
        for(var i = 0; i < count; i++){
            insertImage("","/loader.gif","#gallery");
        }
    }
    function loadAndChangeImages(feature){
        $.getJSON("/pxapi?feature="+feature, changeImages);
    }

     function changeImages(json){
        clearImages();
        var prev_imgs = json.preview_images_urls;
        var imgs = json.images_urls;
        for(var i = 0; i < prev_imgs.length ; i++){
            insertImage(imgs[i],prev_imgs[i],"#gallery");
        }
    }

    function insertImage(href,url, parent){
        var a = $("<a/>").append($( "<img/>" ).attr( "src", url )).attr("href", href);
        $(parent).append(a);
        
    }

    function clearImages(){
        $("#gallery").children().remove();
    }
