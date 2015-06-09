/*********************************************************************
Matt Marchant 2015
http://trederia.blogspot.com

pseuthe Zlib license.

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

//abstract base class for entity components

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <Log.hpp>

#include <memory>

class Entity;
class Message;
class MessageBus;
class Component
{
public:
    using Ptr = std::unique_ptr<Component>;

    enum class Type
    {
        Drawable,
        Physics
    };

    explicit Component(MessageBus&);
    virtual ~Component() = default;

    virtual Type type() const = 0;
    //this is called once per frame by the component's parent entity
    //providing the opportinuty to update each other
    virtual void entityUpdate(Entity&, float) = 0;

    void destroy();
    bool destroyed() const;

protected:
    void sendMessage(const Message&);

private:
    MessageBus& m_messageBus;
    bool m_destroyed;
};

#endif //COMPONENT_HPP_