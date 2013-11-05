dist = 10
angle1 = 0.0
angle2 = 0.0

function onUpdate( delta )
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

   if input.isKeyPressed( input.Right ) then
      angle1 = angle1 + 100.0 * delta
   end

   if input.isKeyPressed( input.Left ) then
      angle1 = angle1 - 100.0 * delta
   end

   if input.isKeyPressed( input.Up ) then
      if input.isKeyPressed( input.LShift ) then
         dist = dist + 10.0 * delta
      else
         angle2 = angle2 + 100.0 * delta
      end
   end

   if input.isKeyPressed( input.Down ) then
      if input.isKeyPressed( input.LShift ) then
         dist = dist - 10.0 * delta
      else
         angle2 = angle2 - 100.0 * delta
      end
   end

   rot1 = glm.rotate( angle1, 0.0, 1.0, 0.0 )
   axis2 = rot1:mul( glm.vec4( 0.0, 0.0, -1.0, 1.0 ) )
   rot2 = glm.rotate( angle2, axis2:get(0), axis2:get(1), axis2:get(2) )
   vecx = rot2:mul( rot1:mul( glm.vec4( dist, 0.0, 0.0, 0.0 ) ) )

   entity.transform:setPosition( vecx:get(0), vecx:get(1), vecx:get( 2 ) )
end
