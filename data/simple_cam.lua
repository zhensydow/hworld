print("hello")

val = 0

function onUpdate( delta )
   --print( "Cam update " .. delta .. " " .. val )
   val = val + delta
   if input.isKeyPressed( input.U ) then
      fov = entity.camera:getFov()
      print( "Key U Pressed " .. fov )
   end

   if input.isKeyPressed( input.I ) then
      print( "Key I Pressed" )
   end
end
