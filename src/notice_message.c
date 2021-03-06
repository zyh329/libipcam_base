#include "notice_message.h"

enum
{
    PROP_0,
    
    IPCAM_NOTICE_MESSAGE_EVENT = 1,
    
    N_PROPERTIES
};

typedef struct _IpcamNoticeMessagePrivate
{
    gchar *event;
} IpcamNoticeMessagePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(IpcamNoticeMessage, ipcam_notice_message, IPCAM_MESSAGE_TYPE);

static GParamSpec *obj_properties[N_PROPERTIES] = {NULL, };

static void ipcam_notice_message_finalize(GObject *self)
{
    IpcamNoticeMessagePrivate *priv = ipcam_notice_message_get_instance_private(IPCAM_NOTICE_MESSAGE(self));
    g_free(priv->event);
    G_OBJECT_CLASS(ipcam_notice_message_parent_class)->finalize(self);
}
static void ipcam_notice_message_get_property(GObject *object,
                                              guint property_id,
                                              GValue *value,
                                              GParamSpec *pspec)
{
    IpcamNoticeMessage *self = IPCAM_NOTICE_MESSAGE(object);
    IpcamNoticeMessagePrivate *priv = ipcam_notice_message_get_instance_private(self);
    switch(property_id)
    {
    case IPCAM_NOTICE_MESSAGE_EVENT:
        {
            g_value_set_string(value, priv->event);
        }
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}
static void ipcam_notice_message_set_property(GObject *object,
                                       guint property_id,
                                       const GValue *value,
                                       GParamSpec *pspec)
{
    IpcamNoticeMessage *self = IPCAM_NOTICE_MESSAGE(object);
    IpcamNoticeMessagePrivate *priv = ipcam_notice_message_get_instance_private(self);
    switch(property_id)
    {
    case IPCAM_NOTICE_MESSAGE_EVENT:
        {
            g_free(priv->event);
            priv->event = g_value_dup_string(value);
            //g_print("ipcam notice message event: %s\n", priv->event);
        }
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}
static void ipcam_notice_message_init(IpcamNoticeMessage *self)
{
    g_object_set(G_OBJECT(self), "type", "notice", "event", "", NULL);
}
static void ipcam_notice_message_class_init(IpcamNoticeMessageClass *klass)
{
    GObjectClass *this_class = G_OBJECT_CLASS(klass);
    this_class->finalize = &ipcam_notice_message_finalize;
    this_class->get_property = &ipcam_notice_message_get_property;
    this_class->set_property = &ipcam_notice_message_set_property;

    obj_properties[IPCAM_NOTICE_MESSAGE_EVENT] =
        g_param_spec_string("event",
                            "Notice message event",
                            "Set notice message event",
                            "", // default value
                            G_PARAM_READWRITE);
    
    g_object_class_install_properties(this_class, N_PROPERTIES, obj_properties);
}
