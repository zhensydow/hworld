print("hello")

val = 0

function onUpdate( delta )
   --print( "Cam update " .. delta .. " " .. val )
   val = val + delta
   if input.isKeyPressed( input.U ) then
      fov = entity.camera:getFov() + 20*delta
      if fov > 80.0 then
         fov = 80.0
      end
      entity.camera:setFov( fov );
   end

   if input.isKeyPressed( input.I ) then
      fov = entity.camera:getFov() - 20*delta
      if fov < 10.0 then
         fov = 10.0
      end
      entity.camera:setFov( fov );
   end
end
